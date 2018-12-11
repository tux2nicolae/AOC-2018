const fs = require("fs");
const input = fs.readFileSync("input.json");

const json = JSON.parse(input);
console.log(json);