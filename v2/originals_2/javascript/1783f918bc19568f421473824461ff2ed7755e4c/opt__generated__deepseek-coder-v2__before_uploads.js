'use strict';

const socketUser = require('./user');
const socketGroup = require('./groups');
const image = require('../image');
const meta = require('../meta');

const inProgress = {};

const uploads = module.exports;

uploads.upload = async function (socket, data) {
	const methodToFunc = {
		'user.uploadCroppedPicture': socketUser.uploadCroppedPicture,
		'user.updateCover': socketUser.updateCover,
		'groups.cover.update': socketGroup.cover.update,
	};
	if (!socket.uid || !data || !data.chunk || !data.params || !data.params.method || !methodToFunc[data.params.method]) {
		throw new Error('[[error:invalid-data]]');
	}

	inProgress[socket.id] = inProgress[socket.id] || {};
	const socketUploads = inProgress[socket.id];
	socketUploads[data.params.method] = socketUploads[data.params.method] || { imageData: '' };
	socketUploads[data.params.method].imageData += data.chunk;

	try {
		const maxSize = (() => {
			switch (data.params.method) {
				case 'user.uploadCroppedPicture': return meta.config.maximumProfileImageSize;
				case 'groups.cover.update': return meta.config.maximumCoverImageSize;
				default: throw new Error('Invalid method');
			}
		})();

		const size = image.sizeFromBase64(socketUploads[data.params.method].imageData);

		if (size > maxSize * 1024) {
			throw new Error(`[[error:file-too-big, ${maxSize}]]`);
		}
		if (socketUploads[data.params.method].imageData.length < data.params.size) {
			return;
		}
		data.params.imageData = socketUploads[data.params.method].imageData;
		const result = await methodToFunc[data.params.method](socket, data.params);
		delete inProgress[socket.id][data.params.method];
		if (Object.keys(inProgress[socket.id]).length === 0) {
			delete inProgress[socket.id];
		}
		return result;
	} catch (err) {
		delete inProgress[socket.id];
		throw err;
	}
};

uploads.clear = function (sid) {
	if (inProgress[sid]) {
		for (const method in inProgress[sid]) {
			delete inProgress[sid][method];
		}
		if (Object.keys(inProgress[sid]).length === 0) {
			delete inProgress[sid];
		}
	}
};
