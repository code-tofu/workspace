import logo from "./logo.svg";
import "./App.css";
import { useState } from "react";

function App() {
  return (
    <div className="App">
      <div className="card">
        <Avatar />
        <div className="data">
          <Intro />
          {/* Should contain one Skill component
        for each web dev skill that you have,
        customized with props */}
          <SkillList />
          <Skill skill="Iron Tail" color="grey" />
        </div>
      </div>
      <Counter />
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

function Avatar() {
  return <img alt="pikachu-avatar" src="avatar.png" className="avatar"></img>;
  // remember that class is className since class is reserved JS
}

function Intro() {
  return (
    <div>
      <h1>Pikachu</h1>
      <h2>Mouse Pokemon</h2>
      <p>
        When several of these POKéMON gather, their electricity could build and
        cause lightning storms.
      </p>
    </div>
  );
}

const moves = [
  {
    skill: "Thunder Wave",
    color: "green",
    prof: 3,
  },
  {
    skill: "Electro Ball",
    color: "yellow",
    prof: 2,
  },
  {
    skill: "Light Screen",
    color: "pink",
    prof: 1,
  },
];

function SkillList() {
  return (
    <div className="skill-list">
      <Skill color="purple" prof={1} />
      <Skill skill="Thunder Shock" color="red" />
      {moves.map((move) => {
        return <Skill skill={move.skill} color={move.color} prof={move.prof} />;
      })}
    </div>
  );
}

function Skill(props) {
  //can destructure
  //note that all the properties are still passed in as prop
  return (
    <div className="skill" style={{ backgroundColor: props.color }}>
      <span>{props.skill ? props.skill : "Tackle"}</span>
      <span> Level-{props.prof}</span>
    </div>
  );
}

function Counter() {
  const [step, setStep] = useState(1);
  const [count, setCount] = useState(0);

  return (
    <div>
      <div>
        {/* (count, step) => setCount(count + step)
          note that the count and step being passed into the event handler function is the reactEvent
        */}
        <button
          onClick={(e) => {
            console.log(e);
            setCount(count - step);
          }}
        >
          -
        </button>
        <span>Count: {count}</span>
        <button onClick={() => setCount(count + step)}>+</button>
      </div>
      <div>
        <button onClick={() => setStep(step - 1)}>-</button>
        {/* callback should take in no state arguments. what is passed from on click is the react synthetic event */}
        <span>Step: {step}</span>
        <button onClick={() => setStep(step + 1)}>+</button>
      </div>
      <div>
        <input type="range" max="10" min="10"></input>
      </div>
    </div>
  );
}

export default App;
