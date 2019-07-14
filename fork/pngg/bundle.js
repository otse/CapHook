(function () {
    'use strict';

    const fs = require('fs');
    var PNG = require('png-js');
    function go() {
        console.log('the appendages');
        //PNG.decode('../../banner.png', function(pixels) {
        PNG.decode('512.png', function (pixels) {
            // pixels is a 1d array (in rgba order) of decoded pixel data
            console.log('woo');
            let obj = {
                pixels: ''
                //array: []
            };
            let binary = Buffer.alloc(pixels.length);
            let string = '';
            let i = 0;
            for (; i < pixels.length; i++) {
                let pixel = pixels[i];
                string += pixel + '/';
                binary.writeUInt8(pixel, i);
            }
            obj.pixels = string;
            fs.writeFile(`./pixels`, binary, () => { });
            fs.writeFile(`./pixels.txt`, string, () => { });
            fs.writeFile(`./pixels.json`, JSON.stringify(obj), () => { });
        });
    }
    go();

}());
