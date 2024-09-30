// Define a new locale called 'es'
defineLocale('es', {
  months: ['enero', 'febrero', ...],
});

// Update the 'es' locale with new configuration
updateLocale('es', {
  weekdays: ['domingo', 'lunes', ...],
});

// Get the 'es' locale
const esLocale = getLocale('es');

// List all defined locales
const locales = listLocales();
