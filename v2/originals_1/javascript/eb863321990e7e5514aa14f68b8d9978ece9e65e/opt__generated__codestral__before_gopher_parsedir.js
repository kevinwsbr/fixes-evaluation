   module.exports = function gopher_parsedir (dirent) {
     const entryPattern = /^(.)(.*?)\t(.*?)\t(.*?)\t(.*?)\u000d\u000a$/
     const entry = dirent.match(entryPattern)

     if (entry === null) {
       throw new Error('Could not parse the directory entry')
     }

     let type
     switch (entry[1]) {
       case 'i':
         type = 255 // GOPHER_INFO
         break
       case '1':
         type = 1 // GOPHER_DIRECTORY
         break
       case '0':
         type = 0 // GOPHER_DOCUMENT
         break
       case '4':
         type = 4 // GOPHER_BINHEX
         break
       case '5':
         type = 5 // GOPHER_DOSBINARY
         break
       case '6':
         type = 6 // GOPHER_UUENCODED
         break
       case '9':
         type = 9 // GOPHER_BINARY
         break
       case 'h':
         type = 254 // GOPHER_HTTP
         break
       default:
         throw new Error(`Unknown entry type: ${entry[1]}`) // Throw error for unknown types instead of returning -1 and data. This provides better feedback to the user about an issue with their input.
     }
     return {
       type: type,
       title: entry[2],
       path: entry[3],
       host: entry[4],
       port: entry[5]
     }
   }
   