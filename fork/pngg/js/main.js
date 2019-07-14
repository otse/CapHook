const fs = require('fs');
var PNG = require('png-js');
function go() {
    PNG.decode('../../banner_ws.png', function (pixels) {
        //PNG.decode('512.png', function(pixels) {
        console.log('woo');
        let binary = Buffer.alloc(pixels.length);
        let i = 0;
        for (; i < pixels.length; i++) {
            let pixel = pixels[i];
            binary.writeUInt8(pixel, i);
        }
        fs.writeFile(`./pink winter soldier`, binary, () => { });
    });
}
go();
