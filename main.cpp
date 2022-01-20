#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "include/sha256.h"
//is supposly the max amount of data can one block handle in the bitcoin blockchain
#define SIZE 5000
using namespace std;

/*Transactio data structure for testing purposes*/
struct TransacationData{
public:
    string Amount[SIZE];
    string senderKey;
    string recieveKey;
};


/**BLOCK CLASS  **/
class Block
{
public:
//block constructor
    Block(TransacationData transaction, int id_block);
    // return the hash of the block 
    string  getHash();
    //hash value of the previous block
    string getPreviousHash();
    //generate the hash of the block
    string hashBuilder(TransacationData transaction, int id_block, string previousHash);
/// hash of the previous block 
    string previousHashBlock;
    int getId();
private:

//index of the block
    int  _ID_block;
//hash of the block 
    string _blockHash;

};
//block constructor
Block::Block(TransacationData transaction, int id_block){ 
    _ID_block= id_block;    
}

//build the hash using the transaction data, id block and the previous block's hash
inline string Block::hashBuilder(TransacationData transaction, int id_block, string previousHash){
    SHA256 sha256;
   stringstream ss;
   ss << transaction.Amount<<transaction.recieveKey<<transaction.senderKey <<id_block << previousHash;
    blockHash = sha256(ss.str());
    return blockHash;
}


string Block::getPreviousHash(){
    return previousHashBlock;
}
string Block::getHash(){
    return blockHash;
}
int Block::getId(){
    return _ID_block;
}

//Transaction data object
TransacationData data1;

/*Blockchain class*/
class Blockchain {
private:
    vector<Block> _chain ;
    Block _GetLastBlock() const;
public:
    Blockchain();
    void addBlock(Block bnew);
};

/*blockchain class implementation*/
Blockchain::Blockchain(){
    //genesis block 
     _chain.emplace_back(Block(data1, 0));
}
void Blockchain::addBlock(Block bnew){
    //store the previous hash
    bnew.previousHashBlock = _GetLastBlock().getHash();
    //generating the hash value of the new block
    bnew.hashBuilder(data1, bnew.getId(), bnew.previousHashBlock);
    //print the hash value
    cout<<bnew.getHash()<<endl;
    //push the block the blockchain array
    _chain.push_back(bnew);
}

Block Blockchain::_GetLastBlock() const {
    //return the last block been added to the blockchain 
    return _chain.back();
}

int main()
{
    data1.Amount[0] ="1000";
    data1.recieveKey = "satoshi";
    data1.senderKey = "edy";
    Blockchain chainBlock;
    chainBlock.addBlock(Block(data1, 1));
    chainBlock.addBlock(Block(data1, 2));
    chainBlock.addBlock(Block(data1, 3));
    chainBlock.addBlock(Block(data1, 4));

    return 0;
}