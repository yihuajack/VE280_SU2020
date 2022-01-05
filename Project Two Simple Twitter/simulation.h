/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server_type.h"

// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.

/*
void visit(...);
void trending(...);
void refresh(...);
void follow(...);
void unfollow(...);
void like(...);
void unlike(...);
void comment(...);
void uncomment(...);
void post(...);
void unpost(...);
*/

/* Helper Functions */

// Server Initialization
void initServer(const string& userfile, Server_t& server);
// Read user information
void readUser(Server_t& server, ifstream& fin, User_t& currentUser, const string& userpath);
// Read post information
void readPost(Server_t& server, ifstream& fin, Post_t& currentPost);
// Logfile processing
void processLog(const string& logfile, Server_t& server);
// Compare function for sorting tags
bool compareTag(const Tag_t& tag1, const Tag_t& tag2);
// Add a post
void Post(ifstream& fin, Post_t& post);
// Delete the post #pid
void Delete(User_t *user1, unsigned int pid);
// Let user1 follows user2
void Follow(User_t *user1, User_t *user2);
// Let user1 unfollows user2
void Unfollow(User_t *user1, User_t *user2);
// Let user1 like user2's post #pid
void Like(User_t *user1, User_t *user2, unsigned int pid);
// Let user1 unlike user2's post #pid
void Unlike(User_t *user1, User_t *user2, unsigned int pid);
// Let user1 comment user2's post #pid
void Comment(ifstream& fin, User_t *user1, User_t *user2, unsigned int pid);
// Let user1 uncomment user2's post #pid
void Uncomment(User_t *user1, User_t *user2, unsigned int pid, unsigned int cid);
// Print user1's and user1's following users' posts
void Refresh(const User_t *user1);
// List tags by their scores
void Trending(unsigned int n, Server_t& server);
// Print relationship between user1 and user2
void Visit(const User_t *user1, const User_t *user2);

// Printing

// Print user information
void printUser(const User_t& user, const string& relationship);
// Print post information
void printPost(const Post_t& post);
// Print tag information
void printTag(const Tag_t& tag, unsigned int rank);

