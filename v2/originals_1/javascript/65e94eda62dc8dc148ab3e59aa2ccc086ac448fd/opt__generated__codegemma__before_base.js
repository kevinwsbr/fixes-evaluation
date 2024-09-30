const context = { /* validation context */ };
const subject = { type: 'string', value: 'hello' };
const schema = { type: 'string', disallow: 'number' };

const valid = validateBase(context, subject, schema);

if (valid) {
  // Subject validates successfully
} else {
  // Subject fails validation
}
