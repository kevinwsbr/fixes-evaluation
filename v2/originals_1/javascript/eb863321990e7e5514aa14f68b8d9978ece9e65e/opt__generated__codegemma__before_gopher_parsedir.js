module.exports = function gopher_parsedir(dirent) {
  //  discuss at: https://locutus.io/php/gopher_parsedir/
  // original by: Brett Zamir (https://brett-zamir.me)
  //   example 1: var entry = gopher_parsedir('0All about my gopher site.\t/allabout.txt\tgopher.example.com\t70\u000d\u000a')
  //   example 1: entry.title
  //   returns 1: 'All about my gopher site.'

  /* Types
   * 0 = plain text file
   * 1 = directory menu listing
   * 2 = CSO search query
   * 3 = error message
   * 4 = BinHex encoded text file
   * 5 = binary archive file
   * 6 = UUEncoded text file
   * 7 = search engine query
   * 8 = telnet session pointer
   * 9 = binary file
   * g = Graphics file format, primarily a GIF file
   * h = HTML file
   * i = informational message
   * s = Audio file format, primarily a WAV file
   */

  const entryPattern = /^\s*(.)(.*?)\t(.*?)\t(.*?)\t(.*?)\s*\u000d\u000a$/;
  const entry = dirent.match(entryPattern);

  if (!entry) {
    throw new Error('Could not parse the directory entry');
  }

  let type = entry[1];
  switch (type) {
    case 'i':
      type = 255;
      break;
    case '1':
      type = 1;
      break;
    case '0':
      type = 0;
      break;
    case '4':
      type = 4;
      break;
    case '5':
      type = 5;
      break;
    case '6':
      type = 6;
      break;
    case '9':
      type = 9;
      break;
    case 'h':
      type = 254;
      break;
    default:
      return {
        type: -1,
        data: dirent,
      }; // GOPHER_UNKNOWN
  }

  return {
    type,
    title: entry[2],
    path: entry[3],
    host: entry[4],
    port: entry[5],
  };
};
