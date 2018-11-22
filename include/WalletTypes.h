// Copyright (c) 2018, The TurtleCoin Developers
// 
// Please see the included LICENSE file for more information.

#pragma once

#include <CryptoNote.h>

#include <unordered_map>

namespace WalletTypes
{
    struct KeyOutput
    {
        Crypto::PublicKey key;
        uint64_t amount;
    };

    /* A coinbase transaction (i.e., a miner reward, there is one of these in
       every block). Coinbase transactions have no inputs. 
       
       We call this a raw transaction, because it is simply key images and
       amounts */
    struct RawCoinbaseTransaction
    {
        /* The outputs of the transaction, amounts and keys */
        std::vector<KeyOutput> keyOutputs;

        /* The hash of the transaction */
        Crypto::Hash hash;

        /* The public key of this transaction, taken from the tx extra */
        Crypto::PublicKey transactionPublicKey;

        /* When this transaction's inputs become spendable. Some genius thought
           it was a good idea to use this field as both a block height, and a
           unix timestamp. If the value is greater than
           CRYPTONOTE_MAX_BLOCK_NUMBER (In cryptonoteconfig) it is treated
           as a unix timestamp, else it is treated as a block height. */
        uint64_t unlockTime;
    };

    /* A raw transaction, simply key images and amounts */
    struct RawTransaction : RawCoinbaseTransaction
    {
        /* The transaction payment ID - may be an empty string */
        std::string paymentID;

        /* The inputs used for a transaction, can be used to track outgoing
           transactions */
        std::vector<CryptoNote::KeyInput> keyInputs;
    };

    /* A 'block' with the very basics needed to sync the transactions */
    struct WalletBlockInfo
    {
        /* The coinbase transaction */
        RawCoinbaseTransaction coinbaseTransaction;

        /* The transactions in the block */
        std::vector<RawTransaction> transactions;

        /* The block height (duh!) */
        uint64_t blockHeight;

        /* The hash of the block */
        Crypto::Hash blockHash;

        /* The timestamp of the block */
        uint64_t blockTimestamp;
    };

    struct TransactionInput
    {
        /* The key image of this amount */
        Crypto::KeyImage keyImage;

        /* The value of this key image */
        uint64_t amount;

        /* The block height this key images transaction was included in
           (Need this for removing key images that were received on a forked
           chain) */
        uint64_t blockHeight;

        /* The transaction public key that was included in the tx_extra of the
           transaction */
        Crypto::PublicKey transactionPublicKey;

        /* The index of this input in the transaction */
        uint64_t transactionIndex;

        /* The index of this output in the 'DB' */
        uint64_t globalOutputIndex;

        /* The transaction key we took from the key outputs */
        Crypto::PublicKey key;
        
        /* If spent, what height did we spend it at. Used to remove spent
           transaction inputs once they are sure to not be removed from a
           forked chain. */
        uint64_t spendHeight;

        /* When does this input unlock for spending. Default is instantly
           unlocked, or blockHeight + CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW
           for a coinbase/miner transaction. Users can specify a custom
           unlock height however. */
        uint64_t unlockTime;

        /* The transaction hash of the transaction that contains this input */
        Crypto::Hash parentTransactionHash;

        bool operator==(const TransactionInput &other)
        {
            return keyImage == other.keyImage;
        }
    };

    /* Includes the owner of the input so we can sign the input with the
       correct keys */
    struct TxInputAndOwner
    {
        TxInputAndOwner(
            const TransactionInput input,
            const Crypto::PublicKey publicSpendKey,
            const Crypto::SecretKey privateSpendKey) :

            input(input),
            publicSpendKey(publicSpendKey),
            privateSpendKey(privateSpendKey)
        {
        }

        TransactionInput input;

        Crypto::PublicKey publicSpendKey;

        Crypto::SecretKey privateSpendKey;
    };

    struct TransactionDestination
    {
        /* The public spend key of the receiver of the transaction output */
        Crypto::PublicKey receiverPublicSpendKey;

        /* The public view key of the receiver of the transaction output */
        Crypto::PublicKey receiverPublicViewKey;

        /* The amount of the transaction output */
        uint64_t amount;
    };

    struct GlobalIndexKey
    {
        uint64_t index;
        Crypto::PublicKey key;
    };

    struct ObscuredInput
    {
        /* The outputs, including our real output, and the fake mixin outputs */
        std::vector<GlobalIndexKey> outputs;

        /* The index of the real output in the outputs vector */
        uint64_t realOutput;

        /* The real transaction public key */
        Crypto::PublicKey realTransactionPublicKey;

        /* The index in the transaction outputs vector */
        uint64_t realOutputTransactionIndex;

        /* The amount being sent */
        uint64_t amount;

        /* The owners keys, so we can sign the input correctly */
        Crypto::PublicKey ownerPublicSpendKey;

        Crypto::SecretKey ownerPrivateSpendKey;
    };

    class Transaction
    {
        public:

            //////////////////
            /* Constructors */
            //////////////////

            Transaction() {};

            Transaction(
                /* Mapping of public key to transaction amount, can be multiple
                   if one transaction sends to multiple subwallets */
                const std::unordered_map<Crypto::PublicKey, int64_t> transfers,
                const Crypto::Hash hash,
                const uint64_t fee,
                const uint64_t timestamp,
                const uint64_t blockHeight,
                const std::string paymentID,
                const uint64_t unlockTime,
                const bool isCoinbaseTransaction) :

                transfers(transfers),
                hash(hash),
                fee(fee),
                timestamp(timestamp),
                blockHeight(blockHeight),
                paymentID(paymentID),
                unlockTime(unlockTime),
                isCoinbaseTransaction(isCoinbaseTransaction)
            {
            }

            /////////////////////////////
            /* Public member functions */
            /////////////////////////////

            int64_t totalAmount() const
            {
                int64_t sum = 0;

                for (const auto [pubKey, amount] : transfers)
                {
                    sum += amount;
                }

                return sum;
            }

            /* It's worth noting that this isn't a conclusive check for if a
               transaction is a fusion transaction - there are some requirements
               it has to meet - but we don't need to check them, as the daemon
               will handle that for us - Any transactions that come to the
               wallet (assuming a non malicious daemon) that are zero and not
               a coinbase, is a fusion transaction */
            bool isFusionTransaction() const
            {
                return fee == 0 && !isCoinbaseTransaction;
            }

            /////////////////////////////
            /* Public member variables */
            /////////////////////////////

            /* A map of public keys to amounts, since one transaction can go to
               multiple addresses. These can be positive or negative, for example
               one address might have sent 10,000 TRTL (-10000) to two recipients
               (+5000), (+5000) 
               
               All the public keys in this map, are ones that the wallet container
               owns, it won't store amounts belonging to random people */
            std::unordered_map<Crypto::PublicKey, int64_t> transfers;

            /* The hash of the transaction */
            Crypto::Hash hash;

            /* The fee the transaction was sent with (always positive) */
            uint64_t fee;

            /* The blockheight this transaction is in */
            uint64_t blockHeight;

            /* The timestamp of this transaction (taken from the block timestamp) */
            uint64_t timestamp;

            /* The paymentID of this transaction (will be an empty string if no pid) */
            std::string paymentID;

            /* When does the transaction unlock */
            uint64_t unlockTime;

            /* Was this transaction a miner reward / coinbase transaction */
            bool isCoinbaseTransaction;
    };

    struct WalletStatus
    {
        /* The amount of blocks the wallet has synced */
        uint64_t walletBlockCount;

        /* The amount of blocks the daemon we are connected to has synced */
        uint64_t localDaemonBlockCount;

        /* The amount of blocks the daemons on the network have */
        uint64_t networkBlockCount;

        /* The amount of peers the node is connected to */
        uint32_t peerCount;

        /* The hashrate (based on the last block the daemon has synced) */
        uint64_t lastKnownHashrate;
    };
}
