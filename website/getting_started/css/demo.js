// demo.js
document.write("Hello JavaScript<br/>");

// variable
var car = "Fiat";

// objects
var pc = {type:"dell", model:"1700", color:"black", width:100, start(){return (pc.type + pc.color)}};
var person = {
    firstName:"John",
    lastName:"Doe",
    age:50,
    eyeColor:"blue"
};

// function

// main code
document.write("You are running " + car + "<br/>");

//document.write("You are using pc: " + pc.type + " - model: " + pc.model + "- width " + pc.width);

//document.write(pc.start());
//document.write(pc.start);

document.write("You are " + person.firstName + " " + person.lastName + ", " + person.age + " years old.");
