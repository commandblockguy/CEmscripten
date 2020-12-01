mergeInto(LibraryManager.library, {
    gfx_Begin: function() {
        class Graphx {
            constructor() {
                this.width = 320;
                this.height = 240;

                this.palette_ptr = ccall('graphx_get_palette', 'number', []);
                this.get_vram_ptr = cwrap('graphx_get_vram', 'number', []);

                this.canvas = document.getElementById('canvas');
                this.canvas.setAttribute('width', this.width);
                this.canvas.setAttribute('height', this.height);

                this.refresh_interval = setInterval(() => {this.update_screen()}, 1000 / 60);
                this.update_screen();
            }

            static rgb1555_to_rgb(rgb1555) {
                const r5 = (rgb1555 >> 10) & 31;
                const g6 = ((rgb1555 >> 4) & 62) | (rgb1555 >> 15);
                const b5 = rgb1555 & 31;
                return new Uint8Array([
                    Math.floor(r5 * 255.0 / 31),
                    Math.floor(g6 * 255.0 / 63),
                    Math.floor(b5 * 255.0 / 31),
                    255
                ]);
            }

            update_screen() {
                //console.log('updating screen');
                let ctx = this.canvas.getContext('2d');
                var imagedata = ctx.createImageData(this.width, this.height);
                var vram_ptr = this.get_vram_ptr();
                var vram = new Uint8Array(HEAPU8.subarray(vram_ptr, vram_ptr + this.width * this.height));
                var palette = [];
                for(let i = 0; i < 256; i++) {
                    let rgb1555 = getValue(this.palette_ptr + 2*i, 'i16');
                    if(rgb1555 < 0) rgb1555 = 0x10000 + rgb1555;
                    palette[i] = Graphx.rgb1555_to_rgb(rgb1555);
                }
                for(let i = 0; i < this.width * this.height; i++) {
                    imagedata.data.set(palette[vram[i]], i * 4);
                }
                ctx.putImageData(imagedata, 0, 0);
                this.refreshed = true;
            }
        }
        Module.graphx = new Graphx();
    },
    gfx_End: function() {
        clearInterval(Module.graphx.refresh_interval);
    }
});
