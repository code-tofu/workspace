function Options({ options, dispatch, answer, correct }) {
  const Answered = answer !== null;
  return (
    <div className="options">
      {options.map((option, index) => (
        <button
          className={`btn btn-option ${index === answer ? "answer" : ""}
          ${Answered ? (index === correct ? "correct" : "wrong") : ""}
            `}
          key={option}
          disabled={Answered}
          onClick={() => dispatch({ type: "newAnswer", payload: index })}
        >
          {option}
        </button>
      ))}
    </div>
  );
}

export default Options;
