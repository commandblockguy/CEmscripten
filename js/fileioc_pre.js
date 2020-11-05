Module.preRun.push(
	function() {
		Module.fileioc = {loaded: false};
		if(typeof FS !== 'undefined') {
			FS.mkdir('/calc');
			FS.mount(IDBFS, {}, '/calc');
			FS.syncfs(true, () => {Module.fileioc.loaded = true;});
			FS.chdir('/calc');
		} else {
			console.log("Skipping filesystem - FS undefined");
		}
	}
);
