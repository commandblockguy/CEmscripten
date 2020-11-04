Module.preRun.push(
	function() {
		Module.fileioc = {loaded: false};
		FS.mkdir('/calc');
		FS.mount(IDBFS, {}, '/calc');
		FS.syncfs(true, () => {Module.fileioc.loaded = true;});
		FS.chdir('/calc');
	}
);
