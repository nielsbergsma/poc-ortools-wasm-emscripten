import createSolver from './example.js'
import exampleWasmData from './example.wasm'

export default { 
  async fetch(request) {
    const method = request.method.toUpperCase();
    if (method !== "POST") {
      return new Response("method not allowed", { status: 405 });
    }

    const body = await request.arrayBuffer();

    // initiate solver
    const solver = await createSolver({
      locateFile: function(path, prefix) {
        return "file://" + path;
      },
      instantiateWasm: function(imports, successCallback) {
        return WebAssembly.instantiate(exampleWasmData, imports).then(successCallback)
      }
    });  

    // copy model data into web assembly
    const modelData = new Int8Array(body);
    const modelAddr = solver._malloc(modelData.length);
    solver.HEAPU8.set(modelData, modelAddr);

    // solve and return solution as string
    const solution = solver._solve(modelAddr, modelData.length);
    return new Response(solution.toString());
  } 
}
