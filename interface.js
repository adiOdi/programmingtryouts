let formulaField = document.getElementById("formula");
function newFormula(event) {
  if (event.keyCode != 13) return;
  formulas.set(formulas.size + "", event.target.value);
  event.target.value = "";
  updateFormDiv();
}
function updateForm(event) {
  if (event.keyCode != 13) return;
  formulas.set(event.target.name, event.target.value);
  updateFormDiv();
}
let varField = document.getElementById("var");
function newVar(event) {
  if (event.keyCode != 13) return;
  if (varField.value == "") return;
  variables.set(varField.value, 0);
  varField.value = "";
  updateVarDiv();
  updateFormDiv();
}
function changeVar(event) {
  if (event.keyCode != 13) return;
  variables.set(event.target.name, event.target.value);
  updateFormDiv();
}
function increaseVar(event) {
  const input = document.getElementById(event.target.name);
  let value = variables.get(input.name) + 1;
  input.value = value;
  variables.set(input.name, value);
  updateFormDiv();
}
function decreaseVar(event) {
  const input = document.getElementById(event.target.name);
  let value = variables.get(input.name) - 1;
  input.value = value;
  variables.set(input.name, value);
  updateFormDiv();
}
let varDiv = document.getElementById("variables");
function updateVarDiv() {
  localStorage.setItem(
    "variables",
    JSON.stringify(Array.from(variables.entries()))
  );
  varDiv.innerHTML = "";
  for (let [key, value] of variables.entries()) {
    const div = document.createElement("div");
    const para = document.createElement("label");
    para.innerText = key;
    para.for = key;
    div.appendChild(para);
    const input = document.createElement("input");
    input.type = "text";
    input.addEventListener("keydown", changeVar);
    input.value = value;
    input.name = key;
    input.id = key;
    div.appendChild(input);
    const btnadd = document.createElement("input");
    btnadd.type = "button";
    btnadd.value = "+";
    btnadd.name = key;
    btnadd.addEventListener("click", increaseVar);
    div.appendChild(btnadd);
    const btnsub = document.createElement("input");
    btnsub.type = "button";
    btnsub.value = "-";
    btnsub.name = key;
    btnsub.addEventListener("click", decreaseVar);
    div.appendChild(btnsub);
    varDiv.appendChild(div);
  }
}

let formDiv = document.getElementById("formulas");
function updateFormDiv() {
  localStorage.setItem(
    "formulas",
    JSON.stringify(Array.from(formulas.entries()))
  );
  localStorage.setItem(
    "variables",
    JSON.stringify(Array.from(variables.entries()))
  );
  formDiv.innerHTML = "";
  let key = 0;
  formulas.forEach((element) => {
    const div = document.createElement("div");
    const input = document.createElement("input");
    input.type = "text";
    input.addEventListener("keydown", updateForm);
    input.value = element;
    input.name = key;
    key++;
    div.appendChild(input);
    const res = document.createElement("p");
    res.innerText = calculate(element);
    div.appendChild(res);
    formDiv.appendChild(div);
  });
}
updateVarDiv();
updateFormDiv();
