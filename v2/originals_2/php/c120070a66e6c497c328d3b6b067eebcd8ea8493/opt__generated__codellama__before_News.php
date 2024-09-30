This is a database class for handling news data in the FAQ system. It includes methods for retrieving, adding, updating and deleting news entries.

The `getNews()` method takes an optional array of parameters as input, which can be used to filter the results based on certain criteria (e.g. date range, language, active status). The method returns a list of news objects, each containing the following properties:

* `id`: Unique ID for the news entry
* `datum`: Date of publication
* `lang`: Language code
* `header`: Header text of the news entry
* `artikel`: Content of the news entry
* `author_name`: Name of the author
* `author_email`: Email address of the author
* `date_start`: Start date of the news entry's validity (if any)
* `date_end`: End date of the news entry's validity (if any)
* `active`: Whether the news entry is active or not
* `comment`: Comment associated with the news entry (optional)
* `link`: Link associated with the news entry (optional)
* `linkTitle`: Title for the link (optional)
* `target`: Target of the link (optional)

The `addNewsEntry()` method takes an array of parameters as input, which should include at least the following properties:

* `date`: Date of publication
* `lang`: Language code
* `header`: Header text of the news entry
* `content`: Content of the news entry
* `authorName`: Name of the author
* `authorEmail`: Email address of the author
* `dateStart`: Start date of the news entry's validity (if any)
* `dateEnd`: End date of the news entry's validity (if any)
* `active`: Whether the news entry is active or not
* `comment`: Comment associated with the news entry (optional)
* `link`: Link associated with the news entry (optional)
* `linkTitle`: Title for the link (optional)
* `target`: Target of the link (optional)

The method returns a boolean value indicating whether the operation was successful.

The `updateNewsEntry()` method takes two arguments: an integer ID and an array of parameters as input, which should include at least the following properties:

* `date`: Date of publication
* `lang`: Language code
* `header`: Header text of the news entry
* `content`: Content of the news entry
* `authorName`: Name of the author
* `authorEmail`: Email address of the author
* `dateStart`: Start date of the news entry's validity (if any)
* `dateEnd`: End date of the news entry's validity (if any)
* `active`: Whether the news entry is active or not
* `comment`: Comment associated with the news entry (optional)
* `link`: Link associated with the news entry (optional)
* `linkTitle`: Title for the link (optional)
* `target`: Target of the link (optional)

The method returns a boolean value indicating whether the operation was successful.

The `deleteNews()` method takes an integer ID as input, which is used to delete the corresponding news entry. The method returns a boolean value indicating whether the operation was successful.