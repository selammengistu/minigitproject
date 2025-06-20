#include <iostream>
#include <fstream> //for reading or writing the file
#include <sstream>  //for string manipulation
#include <ctime>  //for time management
#include <map> //to store filename-hash pairs
#include <vector> //for 
#include <set>  //for unique file names wile using merge
#include <filesystem>  //for directory and file

namespace fs = std::filesystem;      //shorter alias instead of writing std::filesystem everytime. for easiness

// hash function 
std::string simpleHash(const std::string& content) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(content));    
    //creates hash for files
}

// initialization
void init() {
    fs::path repoDir = ".minigit";
    if (fs::exists(repoDir)) {
        std::cout << "MiniGit repo already exists.\n";
        return;
    }
    fs::create_directory(repoDir);
    fs::create_directory(repoDir / "objects");
    fs::create_directory(repoDir / "refs");
    std::ofstream headFile(repoDir / "HEAD");
    headFile << "ref: refs/master";
    headFile.close();
    std::ofstream masterRef(repoDir / "refs/master");
    masterRef.close();
    std::cout << "Initialized empty MiniGit repository in " << fs::absolute(repoDir) << "\n";
    //creates a folder ".minigit"
}

// add files
void add(const std::string& filename) {
    if (!fs::exists(filename)) {
        std::cout << "File not found: " << filename << "\n";
        return;
    }
    std::ifstream inFile(filename);
    std::stringstream buffer;
    buffer << inFile.rdbuf();  //read content inside file
    std::string content = buffer.str();
    inFile.close();
    std::string hash = simpleHash(content); //get hash
    fs::path blobPath = ".minigit/objects/" + hash;
    if (!fs::exists(blobPath)) {  //save content if new
        std::ofstream blobFile(blobPath);
        blobFile << content;
        blobFile.close();
    }
    std::ofstream index(".minigit/index", std::ios::app);
    index << filename << " " << hash << "\n";
    index.close();
    std::cout << "Staged " << filename << " with hash " << hash << "\n"; //stage file
}

// commit
void commit(const std::string& message) {
    std::ifstream index(".minigit/index");
    if (!index.is_open()) {
        std::cout << "Nothing to commit.\n";
        return;
    }
    std::map<std::string, std::string> stagedFiles;
    std::string line;
    while (std::getline(index, line)) {
        std::istringstream iss(line);
        std::string filename, hash;
        iss >> filename >> hash;
        stagedFiles[filename] = hash;
    }
    index.close();
    std::ifstream headFile(".minigit/HEAD");
    std::string refLine;
    std::getline(headFile, refLine);
    headFile.close();
    std::string refPath = refLine.substr(5);  //get branch file
    std::string parentHash;
    std::ifstream parentFile(".minigit/" + refPath);
    std::getline(parentFile, parentHash);
    parentFile.close();
    std::time_t now = std::time(nullptr);
    std::string timestamp = std::to_string(now);
    std::string commitHash = simpleHash(message + timestamp);
    fs::path commitPath = ".minigit/objects/" + commitHash;
    std::ofstream commitFile(commitPath);
    commitFile << "Timestamp: " << timestamp << "\n";
    commitFile << "Message: " << message << "\n";
    commitFile << "Parent: " << parentHash << "\n";
    for (const auto& [filename, hash] : stagedFiles) {
        commitFile << filename << " " << hash << "\n";
    }
    commitFile.close();
    std::ofstream refOut(".minigit/" + refPath);
    refOut << commitHash;
    refOut.close();
    std::remove(".minigit/index");
    std::cout << "Committed changes with hash: " << commitHash << "\n";
    //takes all stage files and saves a commit
}

// view log
void log() {
    std::ifstream headFile(".minigit/HEAD");
    std::string refLine;
    std::getline(headFile, refLine);
    headFile.close();
    std::string refPath = refLine.substr(5);
    std::ifstream refIn(".minigit/" + refPath);
    std::string commitHash;
    std::getline(refIn, commitHash);
    refIn.close();
    while (!commitHash.empty()) {
        fs::path commitPath = ".minigit/objects/" + commitHash;
        std::ifstream commitFile(commitPath);
        std::string timestamp, message, parent;
        std::getline(commitFile, timestamp);
        std::getline(commitFile, message);
        std::getline(commitFile, parent);
        commitFile.close();
        std::cout << "Commit: " << commitHash << "\n" << timestamp << "\n" << message << "\n" << parent << "\n\n";
        commitHash = (parent.substr(0, 8) == "Parent: ") ? parent.substr(8) : "";
    }
    //walkis from head to parent commits
}

// branching
void branch(const std::string& branchName) {
    std::ifstream headFile(".minigit/HEAD");
    std::string refLine;
    std::getline(headFile, refLine);
    headFile.close();
    std::string currentRef = refLine.substr(5);
    std::ifstream currentRefFile(".minigit/" + currentRef);
    std::string currentCommit;
    std::getline(currentRefFile, currentCommit);
    currentRefFile.close();
    std::ofstream newBranch(".minigit/refs/" + branchName);
    newBranch << currentCommit;
    newBranch.close();
    std::cout << "Created branch: " << branchName << "\n";
    //creates a branch by pointing to the current commit
}

// checkout
void checkout(const std::string& target) {
    std::string targetHash;
    fs::path refPath = ".minigit/refs/" + target;
    if (fs::exists(refPath)) {
        std::ifstream refFile(refPath);
        std::getline(refFile, targetHash);
        refFile.close();
        std::ofstream headFile(".minigit/HEAD");
        headFile << "ref: refs/" << target;
        headFile.close();
    } else {
        targetHash = target;
        std::ofstream headFile(".minigit/HEAD");
        headFile << targetHash;
        headFile.close();
    }
    fs::path commitPath = ".minigit/objects/" + targetHash;
    if (!fs::exists(commitPath)) {
        std::cout << "Invalid commit or branch name.\n";
        return;
    }
    std::ifstream commitFile(commitPath);
    std::string line;
    std::getline(commitFile, line);
    std::getline(commitFile, line);
    std::getline(commitFile, line);
    while (std::getline(commitFile, line)) {
        std::istringstream iss(line);
        std::string filename, hash;
        iss >> filename >> hash;
        fs::path blobPath = ".minigit/objects/" + hash;
        std::ifstream blobFile(blobPath);
        std::ofstream outFile(filename);
        outFile << blobFile.rdbuf();
        blobFile.close();
        outFile.close();
    }
    commitFile.close();
    std::cout << "Checked out: " << target << "\n";
    //switches to another commit and restores comtents in the file
}

// merge
void merge(const std::string& branchName) {
    std::string currentRefPath, currentCommitHash, otherCommitHash;
    std::ifstream headFile(".minigit/HEAD");
    std::getline(headFile, currentRefPath);
    currentRefPath = currentRefPath.substr(5);
    headFile.close();
    std::ifstream currentRefFile(".minigit/" + currentRefPath);
    std::getline(currentRefFile, currentCommitHash);
    currentRefFile.close();
    std::ifstream otherRefFile(".minigit/refs/" + branchName);
    if (!otherRefFile.is_open()) {
        std::cout << "Branch not found: " << branchName << "\n";
        return;
        //grabs current commits of the brnanches
    }
    std::getline(otherRefFile, otherCommitHash);
    otherRefFile.close();
    std::map<std::string, std::string> currentFiles, otherFiles;
    std::ifstream commitFile1(".minigit/objects/" + currentCommitHash);
    std::string line;
    std::getline(commitFile1, line);
    std::getline(commitFile1, line);
    std::getline(commitFile1, line);

    //for current commit
    while (std::getline(commitFile1, line)) {
        std::istringstream iss(line);
        std::string filename, hash;
        iss >> filename >> hash;
        currentFiles[filename] = hash;
    }
    commitFile1.close();
    std::ifstream commitFile2(".minigit/objects/" + otherCommitHash);
    std::getline(commitFile2, line);
    std::getline(commitFile2, line);
    std::getline(commitFile2, line);
    //repeat for other file
    while (std::getline(commitFile2, line)) {
        std::istringstream iss(line);
        std::string filename, hash;
        iss >> filename >> hash;
        otherFiles[filename] = hash;
    }
    commitFile2.close();
    std::ofstream index(".minigit/index");
    //combining file names
    std::set<std::string> allFiles;
    for (const auto& [f, _] : currentFiles) allFiles.insert(f);
    for (const auto& [f, _] : otherFiles) allFiles.insert(f);
    for (const auto& file : allFiles) {
        std::string ch = currentFiles[file];
        std::string oh = otherFiles[file];
        if (ch == oh) index << file << " " << ch << "\n";
        else if (ch.empty()) index << file << " " << oh << "\n";
        else if (oh.empty()) index << file << " " << ch << "\n";
        else {
            std::cout << "CONFLICT: both modified " << file << "\n";
            fs::copy_file(".minigit/objects/" + ch, file + ".current", fs::copy_options::overwrite_existing);
            fs::copy_file(".minigit/objects/" + oh, file + ".other", fs::copy_options::overwrite_existing);
        }
    }
    index.close();
    commit("Merged branch " + branchName);
    //compares commits of current and target branches
}

// diff viewer(optional bonus)
void diff(const std::string& hash1, const std::string& hash2) {
    fs::path path1 = ".minigit/objects/" + hash1;
    fs::path path2 = ".minigit/objects/" + hash2;
    if (!fs::exists(path1) || !fs::exists(path2)) {
        std::cout << "Invalid commit hashes.\n";
        return;
    }
    std::ifstream f1(path1), f2(path2);
    std::string line1, line2;
    int lineNum = 1;
    while (std::getline(f1, line1) && std::getline(f2, line2)) {
        if (line1 != line2)
            std::cout << "Line " << lineNum << "\n- " << line1 << "\n+ " << line2 << "\n";
        ++lineNum;
    }
    
    while (std::getline(f1, line1))
        std::cout << "Line " << lineNum++ << "\n- " << line1 << "\n";
    while (std::getline(f2, line2))
        std::cout << "Line " << lineNum++ << "\n+ " << line2 << "\n";
    //shows difference between two blobs
}

//main
int main() {
    std::string command;
    std::cout << "Enter command (init, add <filename>, commit -m <message>, log, branch <name>, checkout <name|hash>, merge <branch>, diff <hash1> <hash2>): ";
    //tskrd input from user
    std::cin >> command;
    if (command == "init") init();
    else if (command == "add") {
        std::string filename;
        std::cin >> filename;
        add(filename);
    } else if (command == "commit") {
        std::string flag, message;
        std::cin >> flag;
        std::getline(std::cin, message);
        if (flag == "-m") commit(message);
        else std::cout << "Invalid commit format. Use: commit -m <message>\n";
    } else if (command == "log") log();
    else if (command == "branch") {
        std::string name;
        std::cin >> name;
        branch(name);
    } else if (command == "checkout") {
        std::string target;
        std::cin >> target;
        checkout(target);
    } else if (command == "merge") {
        std::string name;
        std::cin >> name;
        merge(name);
    } else if (command == "diff") {
        std::string h1, h2;
        std::cin >> h1 >> h2;
        diff(h1, h2);
    } else std::cout << "Unknown command.\n";
    return 0;
    //calles the appropriate functions
}