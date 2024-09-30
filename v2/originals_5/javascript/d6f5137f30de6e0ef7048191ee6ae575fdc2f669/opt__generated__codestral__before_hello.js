 (function(hello) {

	var utils = hello.utils;

	// Save token into the store
	if ('localStorage' in window && 'sessionStorage' in window) {

		// Set the session object
		var item = null,
			expiry = 0,
			now = new Date().getTime(),
			match,
			re = /[#&]access_token=([^&]+)/;

		// Parse the URL
		if ((match = re.exec(location.hash)) || (match = re.exec(location.search))) {
			item = match[1];
		}
		else if ('JSON' in window) {
			try {
				var data = JSON.parse(localStorage.getItem('hellojs_response'));
				if (data && typeof(data)==='object') {
					item = data;
				}
			} catch(e) {}
		}

		// If the item exists and it has an access_token then save it
		if (item && typeof(item)==='string' && re.test(item)) {
			try {
				item = utils.paramsToJSON(item);
			} catch(e) {}
		}

		// If the item exists and it has an access_token then save it
		if (item && typeof(item)==='object' && 'access_token' in item) {

			expiry = now + ((parseInt(item.expires_in, 10) || 3600)*1000);
			item.expires = expiry;

			// Save the authResponse to sessionStorage and localStorage
			try {
				sessionStorage.setItem('hellojs_auth_response', JSON.stringify(item));
				localStorage.setItem('hellojs_auth_response', JSON.stringify(item));
			} catch(e) {}
		}

		// If the item exists and it has an access_token then save it
		if (item && typeof(item)==='object' && 'error' in item) {

			try {
				sessionStorage.setItem('hellojs_auth_response', JSON.stringify(item));
			} catch(e) {}
		}

		// If the access token has expired then delete it from session storage and local storage
		if (now > expiry && 'sessionStorage' in window && 'localStorage' in window) {
			try {
				sessionStorage.removeItem('hellojs_auth_response');
				localStorage.removeItem('hellojs_auth_response');
			} catch(e) {}
		}

	}
})(hello);

// Process a response using an iframe and the hash fragment
(function(window, parent){

	if (parent && window.location != parent.location) {

		var match = /[#&]error=/.exec(window.location.hash),
			re = /([^&]+)=([^&]+)/g,
			params = {},
			result;

		// If there is an error then put it into the params object
		if (match && match[1]) {
			params.error = match[1];
		}

		// Extract parameters from the hash string
		while ((result = re.exec(window.location.hash)) !== null) {
			params[result[1]] = decodeURIComponent(result[2]);
		}

		// If this is a response to an API request and not a login then store it as the last API response
		if (('access_token' in params || 'error' in params) && window.name === 'hellojs') {

			var json = JSON.stringify(params);

			// Send to localStorage if available
			try {
				localStorage.setItem('hellojs_response', json);
			} catch (e) {}

			// Send to sessionStorage if available
			try {
				sessionStorage.setItem('hellojs_response', json);
			} catch (e) {}

			// Send response back to the parent window
			parent.postMessage(json, '*');
		}
	}
})(window, window.parent);