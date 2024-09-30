const Utils = require(__dirname + '/utils.js');

const QueryGenerator = {
  operators: {
    operatorsMap: {
      $eq: ' = ',
      $ne: ' <> ',
      $gt: ' > ',
      $gte: ' >= ',
      $lt: ' < ',
      $lte: ' <= ',
      $in: ' IN ',
      $nin: ' NOT IN ',
      $like: ' LIKE ',
      $notLike: ' NOT LIKE ',
      $between: ' BETWEEN ',
      $notBetween: ' NOT BETWEEN ',
      $regexp: ' REGEXP ',
      $notRegexp: ' NOT REGEXP ',
      $and: ' AND ',
      $or: ' OR ',
      $not: ' NOT '
    },
    operatorsAliases: {
      $eq: 'IS',
      $ne: 'IS NOT',
      $gt: '>',
      $gte: '>=',
      $lt: '<',
      $lte: '<=',
      $in: 'IN',
      $nin: 'NOT IN',
      $like: 'LIKE',
      $notLike: 'NOT LIKE',
      $between: 'BETWEEN',
      $notBetween: 'NOT BETWEEN',
      $regexp: 'REGEXP',
      $notRegexp: 'NOT REGEXP',
      $and: 'AND',
      $or: 'OR',
      $not: 'NOT'
    }
  },

  escape: function(value, field, options) {
    // ... (same as in the original code)
  },

  whereItemsQuery: function(items, options) {
    // ... (same as in the original code)
  },

  handleSequelizeMethod: function(method, tableName, factory, options, prepend) {
    // ... (same as in the original code)
  },

  quoteIdentifier: function(value) {
    // ... (same as in the original code)
  },

  quoteTable: function(value) {
    // ... (same as in the original code)
  },

  getWhereCondition: function(key, value, comparator, escapeOptions, escapeValue) {
    if (!comparator) {
      comparator = ' = ';
    }

    if (escapeValue === undefined) {
      escapeValue = true;
    }

    if (value !== null) {
      if (comparator === 'IS' || comparator === 'IS NOT') {
        comparator = this.operators.operatorsAliases[comparator];
      }

      if (escapeValue) {
        value = this.escape(value, key, escapeOptions);

        // ... (same as in the original code)
      }
    }

    if (key) {
      // ... (same as in the original code)
    }

    return value;
  },

  getWhereConditions: function(smth, tableName, factory, options, prepend) {
    // ... (same as in the original code)
  },

  booleanValue: function(value) {
    return value;
  }
};

module.exports = QueryGenerator;
