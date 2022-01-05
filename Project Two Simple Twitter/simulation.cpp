/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "simulation.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// TODO: Define your functions in this header file.

/* Helper Functions */

// Server Initialization

// REQUIRES: userfile is a valid filename
// MODIFIES: server
// EFFECTS: Open and read in the username file.

void initServer(const string& userfile, Server_t& server) {
    ifstream iUsername(userfile);
    // Check whether userfile is successfully opened.
    if (!iUsername.is_open()) {
        ostringstream oStream;
        oStream << "Error: Cannot open file " << userfile << "!" << endl;
        throw Exception_t(FILE_MISSING, oStream.str());
    }

    string directory;
    getline(iUsername, directory);
    while (getline(iUsername, server.users[server.num_users++].username)) {
        // Check whether the number of users listed in the username file exceeds the maximal number of users MAX_USERS.
        if (server.num_users >= MAX_USERS) {
            ostringstream oStream;
            oStream << "Error: Too many users!" << endl;
            oStream << "Maximal number of users is " << MAX_USERS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }
    }
    server.num_users--;
    for (unsigned int i = 0; i < server.num_users; ++i) {
        ifstream iUserinfo(directory + "/" + server.users[i].username + "/user_info");
        // Check whether user_info is successfully opened.
        if (!iUserinfo.is_open()) {
            ostringstream oStream;
            oStream << "Error: Cannot open file " << directory + "/" + server.users[i].username + "/user_info" << "!" << endl;
            throw Exception_t(FILE_MISSING, oStream.str());
        }

        readUser(server, iUserinfo, server.users[i], directory + "/" + server.users[i].username);
        iUserinfo.close();
    }
    iUsername.close();
}

// REQUIRES: userpath is a valid path
// MODIFIES: server, fin, currentUser
// EFFECTS: Open the personal directories of each users and read in the user information.

void readUser(Server_t& server, ifstream& fin, User_t& currentUser, const string& userpath) {
    string line;
    getline(fin, line);
    unsigned int i, j;
    currentUser.num_posts = stoi(line);
    // Check whether the number of posts listed in the userinfo file exceeds the maximal number of posts MAX_POSTS.
    if (currentUser.num_posts > MAX_POSTS) {
        ostringstream oStream;
        oStream << "Error: Too many posts for user " << currentUser.username << "!" << endl;
        oStream << "Maximal number of posts is " << MAX_POSTS << "." << endl;
        throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
    }

    for (i = 0; i < currentUser.num_posts; ++i) {
        currentUser.posts[i].owner = &currentUser;
        ifstream iPost(userpath + "/posts/" + to_string(i + 1));
        // Check whether postfile is successfully opened.
        if (!iPost.is_open()) {
            ostringstream oStream;
            oStream << "Error: Cannot open file " << userpath + "/posts/" + to_string(i + 1) << "!" << endl;
            throw Exception_t(FILE_MISSING, oStream.str());
        }

        readPost(server, iPost, currentUser.posts[i]);
        iPost.close();
    }
    getline(fin, line);
    currentUser.num_following = stoi(line);
    // Check whether the number of followings listed in the userinfo file exceeds the maximal number of followings MAX_FOLLOWING.
    if (currentUser.num_following > MAX_FOLLOWING) {
        ostringstream oStream;
        oStream << "Error: Too many followings for user " << currentUser.username << "!" << endl;
        oStream << "Maximal number of followings is " << MAX_FOLLOWING << "." << endl;
        throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
    }

    for (i = 0; i < currentUser.num_following; ++i) {
        getline(fin, line);
        for (j = 0; j < server.num_users; ++j) {
            if (server.users[j].username == line) {
                currentUser.following[i] = &server.users[j];
                break;
            }
        }
    }
    getline(fin, line);
    currentUser.num_followers = stoi(line);
    // Check whether the number of followers listed in the userinfo file exceeds the maximal number of followers MAX_FOLLOWERS.
    if (currentUser.num_followers > MAX_FOLLOWERS) {
        ostringstream oStream;
        oStream << "Error: Too many followers for user " << currentUser.username << "!" << endl;
        oStream << "Maximal number of followers is " << MAX_FOLLOWERS << "." << endl;
        throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
    }

    for (i = 0; i < currentUser.num_followers; ++i) {
        getline(fin, line);
        for (j = 0; j < server.num_users; ++j) {
            if (server.users[j].username == line) {
                currentUser.follower[i] = &server.users[j];
                break;
            }
        }
    }
}

// MODIFIES: server, fin, currentPost
// EFFECTS: read in the post information.

void readPost(Server_t& server, ifstream& fin, Post_t& currentPost) {
    string line;
    currentPost.num_tags = 0;
    Post(fin, currentPost);
    getline(fin, line);
    currentPost.num_likes = stoi(line);
    // Check whether the number of likes listed in the post file exceeds the maximal number of likes MAX_LIKES.
    if (currentPost.num_likes > MAX_LIKES) {
        ostringstream oStream;
        oStream << "Error: Too many likes for post " << currentPost.title << "!" << endl;
        oStream << "Maximal number of likes is " << MAX_LIKES << "." << endl;
        throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
    }

    unsigned int i, j;
    for (i = 0; i < currentPost.num_likes; ++i) {
        getline(fin, line);
        for (j = 0; j < server.num_users; ++j) {
            if (server.users[j].username == line) {
                currentPost.like_users[i] = &server.users[j];
                break;
            }
        }
    }
    getline(fin, line);
    currentPost.num_comments = stoi(line);
    // Check whether the number of comments listed in the post file exceeds th e maximal number of comments MAX_COMMENTS.
    if (currentPost.num_comments > MAX_COMMENTS) {
        ostringstream oStream;
        oStream << "Error: Too many comments for post " << currentPost.title << "!" << endl;
        oStream << "Maximal number of comments is " << MAX_COMMENTS << "." << endl;
        throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
    }

    for (i = 0; i < currentPost.num_comments; ++i) {
        getline(fin, line);
        for (j = 0; j < server.num_users; ++j) {
            if (server.users[j].username == line) {
                currentPost.comments[i].user = &server.users[j];
                break;
            }
        }
        getline(fin, currentPost.comments[i].text);
    }
}

// REQUIRES: valid logfile name
// MODIFIES: server
// EFFECTS: Logfile Processing

void processLog(const string& logfile, Server_t& server) {
    ifstream iLogfile(logfile);
    // Check whether logfile is successfully opened.
    if (!iLogfile.is_open()) {
        ostringstream oStream;
        oStream << "Error: Cannot open file " << logfile << "!" << endl;
        throw Exception_t(FILE_MISSING, oStream.str());
    }

    string line, par[5];
    string delimiter = " ";
    size_t start, end;
    unsigned int i, t;
    bool flag = false;
    while (getline(iLogfile, line)) {
        t = 0;
        start = 0;
        flag = false;
        // Parsing logfile commands and arguments.
        while ((end = line.find(delimiter, start)) != string::npos) {
            par[t++] = line.substr(start, end - start);
            start = end + delimiter.length();
        }
        par[t] = line.substr(start, end);

        // Matching commands, arguments, and functions.
        if (par[0] == "trending" && t == 1) {
            cout << ">> " << par[0] << endl;
            Trending(stoi(par[1]), server);
        }
        else {
            User_t *user1 = nullptr;    // Initializing a pointer as a null pointer is mandantory for JOJ tests.
            for (i = 0; i < server.num_users; ++i) {
                if (server.users[i].username == par[0]) {
                    user1 = &server.users[i];
                    flag = true;
                    break;
                }
            }
            if (!flag)
                continue;
            flag = false;
            cout << ">> " << par[1] << endl;
            try {
                if (par[1] == "post") {
                    Post_t &post = user1->posts[user1->num_posts++];
                    post.owner = user1;
                    Post(iLogfile, post);
                } else if (par[1] == "refresh")
                    Refresh(user1);
                else if (par[1] == "delete")
                    Delete(user1, stoi(par[2]));
                else {
                    User_t *user2 = nullptr;    // Initializing a pointer as a null pointer is mandantory for JOJ tests.
                    for (i = 0; i < server.num_users; ++i) {
                        if (server.users[i].username == par[2]) {
                            user2 = &server.users[i];
                            flag = true;
                            break;
                        }
                    }
                    if (!flag)
                        continue;
                    if (par[1] == "follow")
                        Follow(user1, user2);
                    else if (par[1] == "unfollow")
                        Unfollow(user1, user2);
                    else if (par[1] == "like")
                        Like(user1, user2, stoi(par[3]));
                    else if (par[1] == "unlike")
                        Unlike(user1, user2, stoi(par[3]));
                    else if (par[1] == "comment")
                        Comment(iLogfile, user1, user2, stoi(par[3]));
                    else if (par[1] == "uncomment")
                        Uncomment(user1, user2, stoi(par[3]), stoi(par[4]));
                    else if (par[1] == "visit")
                        Visit(user1, user2);
                }
            }
            // Catch processing errors (INVALID_LOG);
            catch (Exception_t &exception) {
                cout << exception.error_info;
            }
        }
    }
}

// MODIFIES: tag1, tag2
// EFFECTS: Compare function for sorting tags.

bool compareTag(const Tag_t& tag1, const Tag_t& tag2) {
    if (tag1.tag_score != tag2.tag_score)
        return tag1.tag_score > tag2.tag_score;
    return tag1.tag_content < tag2.tag_content;
}

// Operation functions.

// MODIFIES: fin, post
// EFFECTS: add a post.

void Post(ifstream& fin, Post_t& post) {
    string line;
    bool flag = false;
    getline(fin, post.title);
    while (getline(fin, line)) {
        if (line.front() == '#') {
            // Repeated tags are counted as only one tag.
            for (unsigned int i = 0; i < post.num_tags; ++i) {
                if (post.tags[i] == line.substr(1, line.length() - 2)) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                continue;
            // Check whether the number of tags listed in the post file exceeds the maximal number of tags MAX_TAGS.
            if (post.num_tags >= MAX_TAGS) {
                ostringstream oStream;
                oStream << "Error: Too many tags for post " << post.title << "!" << endl;
                oStream << "Maximal number of tags is " << MAX_TAGS << "." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
            }

            post.tags[post.num_tags++] = line.substr(1, line.length() - 2);
        }
        // If the string line is not a tag and is already read by getline, then it should be the text of the post.
        else {
            post.text = line;
            break;
        }
    }
}

// MODIFIES: user1
// EFFECTS: delete the post #pid from user1's post list.

void Delete(User_t *user1, unsigned int pid) {
    // Check whether <user 1> has posted post <post_id>.
    if (user1->num_posts < pid) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot delete post #" << pid << "!" << endl;
        oStream << user1->username << " does not have post #" << pid << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }

    while (&user1->posts[pid - 1] != &user1->posts[user1->num_posts - 1]) {
        user1->posts[pid - 1] = user1->posts[pid];
        pid++;
    }
    user1->num_posts--;
}

// MODIFIES: user1, user2
// EFFECTS: add user2 to user1's following list and user1 to user2's followers list.

void Follow(User_t *user1, User_t *user2) {
    // Harmlessly repeated operation to be idempotent though not tested
    for (unsigned  int i = 0; i < user1->num_following; ++i) {
        if (user1->following[i] == user2)
            return;
    }

    user1->following[user1->num_following++] = user2;
    user2->follower[user2->num_followers++] = user1;
}

// MODIFIES: user1, user2
// EFFECTS: delete user2 from user1's following list and user1 from user2's followers list.

void Unfollow(User_t *user1, User_t *user2) {
    unsigned int i, posFollowing = 0, posFollower = 0;
    // Harmlessly repeated operation to be idempotent though not tested
    for (i = 0; i < user1->num_following; ++i) {
        if (user1->following[i] == user2) {
            posFollowing = i + 1;
            break;
        }
    }
    if (posFollowing == 0)
        return;

    while (user1->following[posFollowing - 1] != user1->following[user1->num_following]) {
        user1->following[posFollowing - 1] = user1->following[posFollowing];
        posFollowing++;
    }
    user1->num_following--;
    for (i = 0; i < user2->num_followers; ++i) {
        if (user2->follower[i] == user1) {
            posFollower = i + 1;
            break;
        }
    }
    while (user2->follower[posFollower - 1] != user2->follower[user2->num_followers - 1]) {
        user2->follower[posFollower - 1] = user2->follower[posFollower];
        posFollower++;
    }
    user2->num_followers--;
}

// MODIFIES: user1, user2
// EFFECTS: add user1 to the like_user list of user2's post #pid.

void Like(User_t *user1, User_t *user2, unsigned int pid) {
    // Check whether <user 2> has posted post <post_id>.
    if (user2->num_posts < pid) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot like post #" << pid << " of " << user2->username << "!" << endl;
        oStream << user2->username << " does not have post #" << pid << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }
    // Check whether <user 1> has already liked the post <post_id> of <user 2>.
    for (unsigned int i = 0; i < user2->num_posts; ++i) {
        if (*user2->posts[i].like_users == user1) {
            ostringstream oStream;
            oStream << "Error: " << user1->username << " cannot like post #" << pid << " of " << user2->username << "!" << endl;
            oStream << user1->username << " has already liked post #" << pid << " of " << user2->username << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
            break;
        }
    }

    user2->posts[pid - 1].like_users[user2->posts[pid - 1].num_likes++] = user1;
}

// MODIFIES: user1, user2
// EFFECTS: delete user1 from the like_user list of user2's post #pid.

void Unlike(User_t *user1, User_t *user2, unsigned int pid) {
    unsigned int i, posLikeuser = 0;
    // Check whether <user 2> has posted post <post_id>.
    if (user2->num_posts < pid) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot unlike post #" << pid << " of " << user2->username << "!" << endl;
        oStream << user2->username << " does not have post #" << pid << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }
    for (i = 0; i < user2->posts[pid - 1].num_likes; ++i) {
        if (user2->posts[pid - 1].like_users[i] == user1) {
            posLikeuser = i + 1;
            break;
        }
    }
    // Check whether <user 1> has not liked the post <post_id> of <user 2>.
    if (posLikeuser == 0) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot unlike post #" << pid << " of " << user2->username << "!" << endl;
        oStream << user1->username << " has not liked post #" << pid << " of " << user2->username << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }

    while (user2->posts[pid - 1].like_users[posLikeuser - 1] != user2->posts[pid - 1].like_users[user2->posts[pid - 1].num_likes - 1]) {
        user2->posts[pid - 1].like_users[posLikeuser - 1] = user2->posts[pid - 1].like_users[posLikeuser];
        posLikeuser++;
    }
    user2->posts[pid - 1].num_likes--;
}

// MODIFIES: fin, user1, user2
// EFFECTS: add user1's comment to user2's post #pid.

void Comment(ifstream& fin, User_t *user1, User_t *user2, unsigned int pid) {
    // Check whether <user 2> has posted post <post_id>.
    if (user2->num_posts < pid) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot comment post #" << pid << " of " << user2->username << "!" << endl;
        oStream << user2->username << " does not have post #" << pid << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }

    getline(fin, user2->posts[pid - 1].comments[user2->posts[pid - 1].num_comments].text);
    user2->posts[pid - 1].comments[user2->posts[pid - 1].num_comments++].user = user1;
}

// MODIFIES: user1, user2
// EFFECTS: delete user1's comment #cid of user2's post #pid.

void Uncomment(User_t *user1, User_t *user2, unsigned int pid, unsigned int cid) {
    // Check whether <user 2> has posted post <post_id>.
    if (user2->num_posts < pid) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot uncomment comment #" << cid << " of post #" << pid << " posted by " << user2->username << "!" << endl;
        oStream << user2->username << " does not have post #" << pid << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }
    // Check whether post <post_id> of <user 2> has comment <comment_id>.
    if (user2->posts[pid - 1].num_comments < cid) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot uncomment comment #" << cid << " of post #" << pid << " posted by " << user2->username << "!" << endl;
        oStream << "Post #" << pid << " does not have comment #" << cid << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }
    // Check whether <user 1> is the owner of comment <comment_id> of the post <post_id> by <user 2>.
    if (user2->posts[pid - 1].comments[cid - 1].user != user1) {
        ostringstream oStream;
        oStream << "Error: " << user1->username << " cannot uncomment comment #" << cid << " of post #" << pid << " posted by " << user2->username << "!" << endl;
        oStream << user1->username << " is not the owner of comment #" << cid << "." << endl;
        throw Exception_t(INVALID_LOG, oStream.str());
    }

    while (&user2->posts[pid - 1].comments[cid - 1] != &user2->posts[pid - 1].comments[user2->posts[pid - 1].num_comments - 1]) {
        user2->posts[pid - 1].comments[cid - 1] = user2->posts[pid - 1].comments[cid];
        cid++;
    }
    user2->posts[pid - 1].num_comments--;
}

// EFFECTS: print the posts of user1 and his or her following users' posts.

void Refresh(const User_t *user1) {
    unsigned int i, j;
    for (i = 0; i < user1->num_posts; ++i) {
        printPost(user1->posts[i]);
    }
    for (i = 0; i < user1->num_following; ++i) {
        for (j = 0; j < user1->following[i]->num_posts; ++j) {
            printPost(user1->following[i]->posts[j]);
        }
    }
}

// MODIFIES: server
// EFFECTS: list all the tags by their tag scores.

void Trending(unsigned int n, Server_t& server) {
    unsigned int i, j, k, m;
    bool flag = false;
    // Clear tag scores and number data of previous trending.
    for (i = 0; i < server.num_tags; ++i) {
        server.tags[i].tag_score = 0;
    }
    server.num_tags = 0;

    for (i = 0; i < server.num_users; ++i) {
        for (j = 0; j < server.users[i].num_posts; ++j) {
            for (k = 0; k < server.users[i].posts[j].num_tags; ++k) {
                flag = false;
                // To find if the tag in the post is the same as a previous tag.
                for (m = 0; m < server.num_tags; ++m) {
                    if (server.tags[m].tag_content == server.users[i].posts[j].tags[k]) {
                        server.tags[m].tag_score += 5 + 3 * server.users[i].posts[j].num_comments + server.users[i].posts[j].num_likes;
                        flag = true;
                        break;
                    }
                }
                // If the tag is a new one, initialize it with tag content and score.
                if (!flag) {
                    server.tags[server.num_tags].tag_content = server.users[i].posts[j].tags[k];
                    server.tags[server.num_tags++].tag_score = 5 + 3 * server.users[i].posts[j].num_comments + server.users[i].posts[j].num_likes;
                }
            }
        }
    }
    sort(server.tags, server.tags + server.num_tags, compareTag);
    for (i = 0; i < min(n, server.num_tags); ++i) {
        printTag(server.tags[i], i + 1);
    }
}

// EFFECTS: print the relationship between user1 and user2.

void Visit(const User_t *user1, const User_t *user2) {
    unsigned int i;
    if (user1 == user2)
        printUser(*user1, "");
    else {
        bool following = false, followed = false;
        for (i = 0; i < user1->num_following; ++i) {
            if (user1->following[i] == user2)
                following = true;
        }
        for (i = 0; i < user1->num_followers; ++i) {
            if (user1->follower[i] == user2)
                followed = true;
        }
        if (!following) 
            printUser(*user2, "stranger");
        else if (followed)
            printUser(*user2, "friend");
        else
            printUser(*user2, "following");
    }
}

// Printing

// EFFECTS: print user information.

void printUser(const User_t& user, const string& relationship){
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}

// EFFECTS: print post information.

void printPost(const Post_t& post){
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(unsigned int i = 0; i<post.num_tags; ++i){
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0){
        cout << "Comments:" << endl;
        for(unsigned int i = 0; i<post.num_comments; ++i){
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}

// EFFECTS: print tag information.

void printTag(const Tag_t& tag, unsigned int rank){
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
