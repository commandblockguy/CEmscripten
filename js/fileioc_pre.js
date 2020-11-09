Module.fileioc = {loaded: false, onLoad: []};
Module.preRun.push(
	function() {
		if(typeof FS !== 'undefined') {
			FS.mkdir('/calc');
			FS.mount(IDBFS, {}, '/calc');
			FS.syncfs(true, () => {
				Module.fileioc.onLoad.forEach(f => f());
				Module.fileioc.loaded = true;
			});
		} else {
			console.log("Skipping filesystem - FS undefined");
		}
	}
);
