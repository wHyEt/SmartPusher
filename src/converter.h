
/*
 * This HTML code will be injected in /setup webpage using a <div></div> element as parent
 * The parent element will hhve the HTML id properties equal to 'raw-html-<id>'
 * where the id value will be equal to the id parameter passed to the function addHTML(html_code, id).
 */
static const char custom_html[] PROGMEM = R"EOF(
	<div class="wrapper">
		<section class="section bottom-divider">
			<section class="sub-section">
				<div class="column" id="file-input-column">
					<h2 class="sub-section-title">1. Select image</h2>
					<input type="file" id="file-input" name="file-input" multiple /><br />
				</div>

			</section>
		</section>

		<section class="section bottom-divider">
			<h2>2. Image Settings</h2>
			<section class="sub-section">
				<div class="table">

					<div class="table-row">
						<div class="table-cell"><label>Canvas size: </label></div>
						<div class="table-cell">
							<ul class="size-input" id="image-size-settings"></ul>
							<div id="only-images-file-error" class="msg error-msg">Only images file type are allowed
							</div>
						</div>
					</div>

					<div class="table-row">
						<div class="table-cell"><label>Background color:</label></div>
						<div class="table-cell">
							<input id="backgroundColorBlack" type="radio" name="backgroundColor" value="black"
								checked="checked" onchange="updateRadio('backgroundColor')" />
							<label for="backgroundColorBlack" class="smallLabel">Black</label>
							<input id="backgroundColorWhite" type="radio" name="backgroundColor" value="white"
								onchange="updateRadio('backgroundColor')" />
							<label for="backgroundColorWhite" class="smallLabel">White</label>
						</div>
					</div>

					<div class="table-row">
						<div class="table-cell"><label for="invertColors">Invert image colors</label></div>
						<div class="table-cell">
							<input id="invertColors" type="checkbox" onchange="updateBoolean('invertColors')" />
						</div>
					</div>

					<div class="table-row">
						<div class="table-cell"><label>Brightness / alpha threshold: </label></div>
						<div class="table-cell">
							<input id="threshold" class="size-input" type="number" min="0" max="255" name="threshold"
								oninput="updateInteger('threshold')" value="128" />
							<div class="note">
								<i>0 - 255; if the brightness of a pixel is above the given level the pixel becomes
									white, otherwise they become black. When using alpha, opaque and transparent are
									used instead.</i>
							</div>
						</div>
					</div>

					<div class="table-row">
						<div class="table-cell"><label for="scale">Scaling</label></div>
						<div class="table-cell">
							<select id="scale" name="scale" onchange="updateInteger('scale')">

								<option value="2">scale to fit, keeping proportions</option>
								<option value="3">stretch to fill canvas</option>
								<option value="4">stretch to fill canvas horizontally</option>
								<option value="5">stretch to fill canvas vertically</option>
								<option value="1">original size</option>
							</select>
						</div>
					</div>

					<div class="table-row">
						<div class="table-cell"><label>Center:</label></div>
						<div class="table-cell">
							<input id="centerHorizontally" type="checkbox"
								onchange="updateBoolean('centerHorizontally')" />
							<label for="centerHorizontally">horizontally</label>
							<input id="centerVertically" type="checkbox" onchange="updateBoolean('centerVertically')" />
							<label for="centerVertically">vertically</label>
						</div>
					</div>

					<div class="table-row">
						<div class="table-cell"><label for="invertColors">Rotate image:</label></div>
						<div class="table-cell">
							<input id="rotate180" type="checkbox" onchange="updateBoolean('rotate180')" />
							<label for="rotate180">rotate 180 degrees</label>
						</div>
					</div>

					<div class="table-row">
						<div class="table-cell"><label>Flip:</label></div>
						<div class="table-cell">
							<input id="flipHorizontally" type="checkbox" onchange="updateBoolean('flipHorizontally')" />
							<label for="flipHorizontally">horizontally</label>
							<input id="flipVertically" type="checkbox" onchange="updateBoolean('flipVertically')" />
							<label for="flipVertically">vertically</label>
						</div>
					</div>
				</div>
				<div class="note">
					<i>Note: centering the image only works when using a canvas larger than the original image.</i>
				</div>
			</section>
		</section>

		<section class="section bottom-divider">
			<h2>3. Preview</h2>
			<section class="sub-section">
				<div id="images-canvas-container"></div>
			</section>
		</section>



		<section class="sub-section">
			<button type="button" class="generate-button" onclick="outputString()">Generate</button>

		</section>
		</section>
	</div>
)EOF";

static const char custom_css[] PROGMEM = R"EOF(
		* {
			margin: 0;
			padding: 0;
		}

		body {
			font-family: arial;
		}

		.wrapper {
			display: flex;
			flex-direction: column;
			margin: auto;
			width: 100%;
		}

		.section {
			margin: 10px 0;
		}

		.bottom-divider {
			border-bottom: 2px solid #000000;
			padding-bottom: 20px;
		}

		.sub-section {
			clear: both;
			margin-bottom: 1px;
		}

		.section,
		.sub-section {
			width: 100%;
		}

		.column {
			float: left;
		}

		.column-center {
			min-width: 160px;
			text-align: center;
		}

		.column-right {
			float: right;
		}

		.sub-section-title {
			margin: 0 0 10px;
		}

		p {
			margin: 20px 0;
		}

		.table {
			display: table;
			margin: 10px 0 0;
			width: 100%;
		}

		.table-row {
			display: table-row;
			width: 100%;
		}

		.table-cell {
			display: table-cell;
			padding: 5px 0;
		}

		.table-cell:first-child {
			width: 30%;
		}

		.table-cell:last-child {
			width: 70%;
		}

		.table-cell:first-child label {
			font-weight: bold;
		}

		.table-cell:last-child label {
			margin-right: 10px;
		}

		.nested-table {
			margin: 0;
		}

		.nested-table .table-cell {
			color: #666;
			font-size: .9em;
			width: 200px;
		}

		#format-caption-container div {
			color: #505050;
			display: none;
			font-size: .9em;
			line-height: 1.4em;
			padding: 10px 0 15px;
			width: 100%;
		}

		.note {
			color: #666666;
			font-size: .9em;
			line-height: 1.4em;
			margin: 3px 0;
		}

		.file-input-entry {
			display: flex;
			justify-content: space-between;
			margin-bottom: 10px;
		}

		.generate-button {
			margin: 40px 0 20px;
		}

		.remove-button {
			margin: 0 0 0 10px;
			padding: 1px 4px;
		}

		.file-info {
			color: #505050;
			font-size: .7em;
			margin-left: 0px;
			max-width: 300px;
			white-space: pre;
		}

		.size-input {
			width: 125px;
		}

		.glyph-input {
			width: 80px;
			margin-left: 10px;
		}

		#image-size-settings {
			list-style-type: none;
		}

		#image-size-settings li {
			margin: 4px 0;
		}

		#images-canvas-container {
			align-items: flex-start;
			display: flex;
			flex-wrap: wrap;
		}

		#arduino-identifier,
		#adafruit-gfx-settings,
		#all-same-size {
			display: none;
		}

		.msg {
			font-size: 1.2em;
		}

		.error-msg {
			color: #ff0000;
			display: none;
		}
	)EOF";

static const char custom_script[] PROGMEM = R"EOF(
	var __output;

		// Output the image as a string for horizontally drawing displays
		function horizontal1bit(data, canvasWidth, canvasHeight, filname) {
			var output = new Uint8Array(Math.ceil(canvasWidth * canvasHeight / 8) + 2);
			var output_index = 0;

			// Write the width and height to the output buffer
			output[0] = canvasWidth;
			output[1] = canvasHeight;

			var byteIndex = 0;
			var number = 0;

			// format is RGBA, so move 4 steps per pixel
			for (var index = 0; index < data.length; index += 4) {
				// Get the average of the RGB (we ignore A)
				var avg = (data[index] + data[index + 1] + data[index + 2]) / 3;
				if (avg > settings["threshold"]) {
					number += Math.pow(2, byteIndex);
				}
				byteIndex++;

				// if this was the last pixel of a row or the last pixel of the
				// image, fill up the rest of our byte with zeros so it always contains 8 bits
				if ((index != 0 && (((index / 4) + 1) % (canvasWidth)) == 0) || (index == data.length - 4)) {
					var paddingBits = 8 - byteIndex;
					number = number << paddingBits;
					output[output_index + 2] = number;
					output_index++;
					number = 0;
					byteIndex = 0;
				}

				// When we have the complete 8 bits, write them to the output buffer
				if (byteIndex >= 8) {
					output[output_index + 2] = number;
					output_index++;
					number = 0;
					byteIndex = 0;
				}
			}

			// Write the output buffer to a file
			var blob = new Blob([output], { type: "application/octet-stream" });
			var formData = new FormData();
			formData.append("data", blob, '/' + filname + '.bin');

			// POST data using the Fetch API
			fetch('/edit', {
				method: 'POST',
				mode: 'cors',
				body: formData
			})

				// Handle the server response
				.then(response => response.text())
				.then(text => {
					openModalMessage('Success!', '<br>Image saved as ' + filname + '<br>');
				});
		};

		// An images collection with helper methods
		function Images() {
			var collection = [];
			this.push = function (img, canvas, glyph) {
				collection.push({ "img": img, "canvas": canvas, "glyph": glyph });
			};
			this.remove = function (image) {
				var i = collection.indexOf(image);
				if (i != -1) collection.splice(i, 1);
			};
			this.each = function (f) { collection.forEach(f); };
			this.length = function () { return collection.length; };
			this.first = function () { return collection[0]; };
			this.last = function () { return collection[collection.length - 1]; };
			this.getByIndex = function (index) { return collection[index]; };
			this.setByIndex = function (index, img) { collection[index] = img; };
			this.get = function (img) {
				if (img) {
					for (var i = 0; i < collection.length; i++) {
						if (collection[i].img == img) {
							return collection[i];
						}
					}
				}
				return collection;
			};
			return this;
		}

		// Add events to the file input button
		var fileInput = document.getElementById("file-input");
		fileInput.addEventListener("click", function () { this.value = null; }, false);
		fileInput.addEventListener("change", handleImageSelection, false);

		var fileInputColumn = document.getElementById("file-input-column");

		// Filetypes accepted by the file picker
		var fileTypes = ["jpg", "jpeg", "png", "bmp", "gif", "svg"];

		// The canvas we will draw on
		var canvasContainer = document.getElementById("images-canvas-container");
		var imageSizeSettings = document.getElementById("image-size-settings");
		var images = new Images();

		// A bunch of settings used when converting
		var settings = {
			screenWidth: 128,
			screenHeight: 64,
			scaleToFit: true,
			preserveRatio: true,
			centerHorizontally: false,
			centerVertically: false,
			flipHorizontally: false,
			flipVertically: false,
			backgroundColor: "white",
			scale: "1",
			drawMode: "horizontal",
			threshold: 128,
			outputFormat: "plain",
			invertColors: false,
			rotate180: false
		};

		// Variable name, when "arduino code" is required
		var identifier = "myBitmap";

		function update() {
			images.each(function (image) { place_image(image); });
		}

		// Easy way to update settings controlled by a textfield
		function updateInteger(fieldName) {
			settings[fieldName] = document.getElementById(fieldName).value;
			update();
		}

		// Easy way to update settings controlled by a checkbox
		function updateBoolean(fieldName) {
			settings[fieldName] = document.getElementById(fieldName).checked;
			update();
		}

		// Easy way to update settings controlled by a radiobutton
		function updateRadio(fieldName) {
			var radioGroup = document.getElementsByName(fieldName);
			for (var i = 0; i < radioGroup.length; i++) {
				if (radioGroup[i].checked) {
					settings[fieldName] = radioGroup[i].value;
				}
			}
			update();
		}


		// Make the canvas black and white
		function blackAndWhite(canvas, ctx) {
			var imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
			var data = imageData.data;
			for (var i = 0; i < data.length; i += 4) {
				var avg = (data[i] + data[i + 1] + data[i + 2]) / 3;
				avg > settings["threshold"] ? avg = 255 : avg = 0;
				data[i] = avg; // red
				data[i + 1] = avg; // green
				data[i + 2] = avg; // blue
			}
			ctx.putImageData(imageData, 0, 0);
		}

		// Invert the colors of the canvas
		function invert(canvas, ctx) {
			var imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
			var data = imageData.data;
			for (var i = 0; i < data.length; i += 4) {
				data[i] = 255 - data[i];     // red
				data[i + 1] = 255 - data[i + 1]; // green
				data[i + 2] = 255 - data[i + 2]; // blue
			}
			ctx.putImageData(imageData, 0, 0);
		}

		// Draw the image onto the canvas, taking into account color and scaling
		function place_image(image) {

			var img = image.img;
			var canvas = image.canvas;
			canvas.style.border = "2px solid red";
			var ctx = canvas.getContext("2d");
			image.ctx = ctx;

			// Invert background if needed
			if (settings["backgroundColor"] == "transparent") {
				ctx.fillStyle = "rgba(0,0,0,0.0)";
				ctx.globalCompositeOperation = 'copy';
			} else {
				if (settings["invertColors"]) {
					settings["backgroundColor"] == "white" ? ctx.fillStyle = "black" : ctx.fillStyle = "white";
				} else {
					ctx.fillStyle = settings["backgroundColor"];
				}
				ctx.globalCompositeOperation = 'source-over';
			}
			ctx.fillRect(0, 0, canvas.width, canvas.height);

			ctx.setTransform(1, 0, 0, 1, 0, 0); // start with identity matrix transform (no rotation).
			if (settings["rotate180"]) {
				// Matrix transformation
				ctx.translate(canvas.width / 2.0, canvas.height / 2.0);
				ctx.rotate(Math.PI);
				ctx.translate(-canvas.width / 2.0, -canvas.height / 2.0);
			}


			// Offset used for centering the image when requested
			var offset_x = 0;
			var offset_y = 0;

			switch (settings["scale"]) {
				case "1": // Original
					if (settings["centerHorizontally"]) { offset_x = Math.round((canvas.width - img.width) / 2); }
					if (settings["centerVertically"]) { offset_y = Math.round((canvas.height - img.height) / 2); }
					ctx.drawImage(img, 0, 0, img.width, img.height,
						offset_x, offset_y, img.width, img.height);
					break;
				case "2": // Fit (make as large as possible without changing ratio)
					var horRatio = canvas.width / img.width;
					var verRatio = canvas.height / img.height;
					var useRatio = Math.min(horRatio, verRatio);

					if (settings["centerHorizontally"]) { offset_x = Math.round((canvas.width - img.width * useRatio) / 2); }
					if (settings["centerVertically"]) { offset_y = Math.round((canvas.height - img.height * useRatio) / 2); }
					ctx.drawImage(img, 0, 0, img.width, img.height,
						offset_x, offset_y, img.width * useRatio, img.height * useRatio);
					break;
				case "3": // Stretch x+y (make as large as possible without keeping ratio)
					ctx.drawImage(img, 0, 0, img.width, img.height,
						offset_x, offset_y, canvas.width, canvas.height);
					break;
				case "4": // Stretch x (make as wide as possible)
					offset_x = 0;
					if (settings["centerVertically"]) { Math.round(offset_y = (canvas.height - img.height) / 2); }
					ctx.drawImage(img, 0, 0, img.width, img.height,
						offset_x, offset_y, canvas.width, img.height);
					break;
				case "5": // Stretch y (make as tall as possible)
					if (settings["centerHorizontally"]) { offset_x = Math.round((canvas.width - img.width) / 2); }
					offset_y = 0;
					ctx.drawImage(img, 0, 0, img.width, img.height,
						offset_x, offset_y, img.width, canvas.height);
					break;
			}
			// Make sure the image is black and white

			blackAndWhite(canvas, ctx);
			if (settings["invertColors"]) {
				invert(canvas, ctx);
			}


			// Flip image if needed
			if (settings["flipHorizontally"]) {
				ctx.save();
				ctx.scale(-1, 1);
				ctx.drawImage(canvas, -canvas.width, 0);
				ctx.restore();
			}
			if (settings["flipVertically"]) {
				ctx.save();
				ctx.scale(1, -1);
				ctx.drawImage(canvas, 0, -canvas.height);
				ctx.restore();
			}
		}


		// Handle selecting an image with the file picker
		function handleImageSelection(evt) {
			images.each(function (image) {
				images.remove(image);
			});
			imageSizeSettings.innerHTML = "";
			update();

			canvasContainer.innerHTML = '';
			var files = evt.target.files;
			for (var i = 0, f; f = files[i]; i++) {

				// Only process image files.
				if (!f.type.match("image.*")) {

					continue;
				}

				var reader = new FileReader();

				reader.onload = (function (file) {
					return function (e) {
						// Render thumbnail.

						var img = new Image();

						img.onload = function () {
							const fileInputColumnEntry = document.createElement("div");
							fileInputColumnEntry.className = "file-input-entry";




							var canvas = document.createElement("canvas");

							var imageEntry = document.createElement("li");
							imageEntry.setAttribute("data-img", file.name);

							var w = document.createElement("input");
							w.type = "number";
							w.name = "width";
							w.id = "screenWidth";
							w.min = 0;
							w.max = 128;
							w.className = "size-input";
							w.value = img.width;
							settings["screenWidth"] = img.width;
							w.oninput = function () { canvas.width = this.value; update(); updateInteger('screenWidth'); };

							var h = document.createElement("input");
							h.type = "number";
							h.name = "height";
							h.id = "screenHeight";
							h.min = 0;
							h.max = 64;
							h.className = "size-input";
							h.value = img.height;
							settings["screenHeight"] = img.height;
							h.oninput = function () { canvas.height = this.value; update(); updateInteger('screenHeight'); };


							var fn = document.createElement("span");
							fn.className = "file-info";
							fn.innerHTML = "File resolution: " + img.width + " x " + img.height;
							fn.innerHTML += "<br />";



							fileInputColumn.appendChild(fileInputColumnEntry);

							imageEntry.appendChild(fn);

							var sn = document.createElement("span");
							sn.appendChild(w);
							sn.appendChild(document.createTextNode(" x "));
							sn.appendChild(h);
							imageEntry.appendChild(sn);

							imageSizeSettings.appendChild(imageEntry);


							if (img.width > 128) {
								canvas.width = 128;
								w.value = 128;
							} else {
								canvas.width = img.width;
							}

							if (img.height > 64) {
								canvas.height = 64;
								h.value = 64;
							} else {
								canvas.height = img.height;
							}


							canvasContainer.appendChild(canvas);

							images.push(img, canvas, file.name.split(".")[0]);
							place_image(images.last());
							updateInteger("scale");
							updateRadio('backgroundColor')

						};
						img.src = e.target.result;
					};
				})(f);
				reader.readAsDataURL(f);
			}
		}

		function imageToString(image) {
			// extract raw image data
			var ctx = image.ctx;
			var canvas = image.canvas;

			var imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
			var data = imageData.data;
			horizontal1bit(data, canvas.width, canvas.height, image.glyph);
		}

		// Get the custom arduino output variable name, if any
		function getIdentifier() {
			var vn = document.getElementById("identifier");
			return vn && vn.value.length ? vn.value : identifier;
		}

		// Output the image string to the textfield
		function outputString() {
			var output_string = "", count = 1;
			var code = "";
			var comment = "";
			imageToString(images.first());
		}

		function copyOutput() {
			navigator.clipboard.writeText(__output);
		}

		// Use the horizontally oriented list to draw the image
		function listToImageHorizontal(list, canvas) {

			var ctx = canvas.getContext("2d");
			ctx.clearRect(0, 0, canvas.width, canvas.height);

			var imgData = ctx.createImageData(canvas.width, canvas.height);

			var index = 0;

			var page = 0;
			var x = 0;
			var y = 7;
			// round the width up to the next byte
			var widthRoundedUp = Math.floor(canvas.width / 8 + (canvas.width % 8 ? 1 : 0)) * 8;
			var widthCounter = 0;

			// Move the list into the imageData object
			for (var i = 0; i < list.length; i++) {

				var binString = hexToBinary(list[i]);
				if (!binString.valid) {
					alert("Something went wrong converting the string. Did you forget to remove any comments from the input?");
					console.log("invalid hexToBinary: ", binString.s);
					return;
				}
				binString = binString.result;
				if (binString.length == 4) {
					binString = binString + "0000";
				}

				// Check if pixel is white or black
				for (var k = 0; k < binString.length; k++, widthCounter++) {
					// if we've counted enough bits, reset counter for next line
					if (widthCounter >= widthRoundedUp) {
						widthCounter = 0;
					}
					// skip 'artifact' pixels due to rounding up to a byte
					if (widthCounter >= canvas.width) {
						continue;
					}
					var color = 0;
					if (binString.charAt(k) == "1") {
						color = 255;
					}
					imgData.data[index] = color;
					imgData.data[index + 1] = color;
					imgData.data[index + 2] = color;
					imgData.data[index + 3] = 255;

					index += 4;
				}
			}

			// Draw the image onto the canvas, then save the canvas contents
			// inside the img object. This way we can reuse the img object when
			// we want to scale / invert, etc.
			ctx.putImageData(imgData, 0, 0);
			var img = new Image();
			img.src = canvas.toDataURL("image/png");
			images.first().img = img;
		}

		// Use the vertically oriented list to draw the image
		function listToImageVertical(list, canvas) {

			var ctx = canvas.getContext("2d");
			ctx.clearRect(0, 0, canvas.width, canvas.height);

			var index = 0;

			var page = 0;
			var x = 0;
			var y = 7;

			// Move the list into the imageData object
			for (var i = 0; i < list.length; i++) {

				var binString = hexToBinary(list[i]);
				if (!binString.valid) {
					alert("Something went wrong converting the string. Did you forget to remove any comments from the input?");
					console.log("invalid hexToBinary: ", binString.s);
					return;
				}
				binString = binString.result;
				if (binString.length == 4) {
					binString = binString + "0000";
				}

				// Check if pixel is white or black
				for (var k = 0; k < binString.length; k++) {
					var color = 0;
					if (binString.charAt(k) == "1") {
						color = 255;
					}
					drawPixel(ctx, x, (page * 8) + y, color);
					y--;
					if (y < 0) {
						y = 7;
						x++;
						if (x >= settings["screenWidth"]) {
							x = 0;
							page++;
						}
					}

				}
			}
			// Save the canvas contents inside the img object. This way we can
			// reuse the img object when we want to scale / invert, etc.
			var img = new Image();
			img.src = canvas.toDataURL("image/png");
			images.first().img = img;
		}

		// Convert hex to binary
		function hexToBinary(s) {

			var i, k, part, ret = "";
			// lookup table for easier conversion. "0" characters are
			// padded for "1" to "7"
			var lookupTable = {
				"0": "0000", "1": "0001", "2": "0010", "3": "0011", "4": "0100",
				"5": "0101", "6": "0110", "7": "0111", "8": "1000", "9": "1001",
				"a": "1010", "b": "1011", "c": "1100", "d": "1101", "e": "1110",
				"f": "1111", "A": "1010", "B": "1011", "C": "1100", "D": "1101",
				"E": "1110", "F": "1111"
			};
			for (i = 0; i < s.length; i += 1) {
				if (lookupTable.hasOwnProperty(s[i])) {
					ret += lookupTable[s[i]];
				} else {
					return { valid: false, s: s };
				}
			}
			return { valid: true, result: ret };
		}

		// Quick and effective way to draw single pixels onto the canvas
		// using a global 1x1px large canvas
		function drawPixel(ctx, x, y, color) {
			var single_pixel = ctx.createImageData(1, 1);
			var d = single_pixel.data;

			d[0] = color;
			d[1] = color;
			d[2] = color;
			d[3] = 255;
			ctx.putImageData(single_pixel, x, y);
		}

		// get the type (in arduino code) of the output image
		// this is a bit of a hack, it's better to make this a property of the conversion function (should probably turn it into objects)
		function getType() {
			if (settings.conversionFunction == ConversionFunctions.horizontal565) {
				return "uint16_t";
			} else if (settings.conversionFunction == ConversionFunctions.horizontal888) {
				return "unsigned long";
			} else {
				return "unsigned char";
			}
		}
)EOF";