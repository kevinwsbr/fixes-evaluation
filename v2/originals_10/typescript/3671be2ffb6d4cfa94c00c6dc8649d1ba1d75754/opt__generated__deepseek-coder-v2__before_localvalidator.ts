const validator = new SlpTransactionValidator();
const validTxIds = await validator.validateSlpTransactions(['txid1', 'txid2']);
console.log(validTxIds); // Outputs the list of validated txids
