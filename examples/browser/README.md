# Browser example

Runs example.{js,wasm} as a service worker in the browser. Tested with Chrome, Firefox and Safari.

## Note

For Firefox, example.js (emscripten generated) needs to merged in with worker.js. Firefox <= 110 doesn't support to dynamic load modules in service workers. [This is fixed](https://bugzilla.mozilla.org/show_bug.cgi?id=1540913), but not yet released.

## Run

Spin up a simple web server in the current directory, to access the page locally. E.g.

```shell
python3 -m http.server 9000

```

The page can now be opened in your favorite browser at [http://localhost:9000/example.html](http://localhost:9000/example.html). Inspect the console log to see the output.