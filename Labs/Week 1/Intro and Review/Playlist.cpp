//Done possibly with the loving help of Hannah Bach <3 hbach003
#include <string>
#include <iostream>

#include "Playlist.h"

using namespace std;

PlaylistNode::PlaylistNode() {
  uniqueID = "none";
  songName = "none";
  artistName = "none";
  songLength = 0;
  nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string id, string name, string artist, int length, PlaylistNode* nextLoc) {
  uniqueID = id;
  songName = name;
  artistName = artist;
  songLength = length;
  nextNodePtr = 0;
  
}

void PlaylistNode::InsertAfter(PlaylistNode* nextLoc) {
  PlaylistNode *temp = nullptr;

  temp = this->nextNodePtr;
  this->nextNodePtr = nextLoc;
  nextLoc->nextNodePtr = temp;
}

void PlaylistNode::SetNext(PlaylistNode* next) {
  this->nextNodePtr = next;
} 

string PlaylistNode::GetID() const {
  return uniqueID;
}

string PlaylistNode::GetSongName() const {
  return songName;
}

string PlaylistNode::GetArtistName() const {
  return artistName;
}

int PlaylistNode::GetSongLength() const {
  return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
  return this->nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() {
  cout << "Unique ID: " << uniqueID << endl;
  cout << "Song Name: " << songName << endl;
  cout << "Artist Name: " << artistName << endl;
  cout << "Song Length (in seconds): " << songLength << endl << endl;
}

