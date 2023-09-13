function FinishScreen({ score, maxPoints, highScore, dispatch }) {
  const percentageScore = (score / maxPoints) * 100;
  return (
    <>
      <p className="result">
        Your final score is {score} out of {maxPoints} (
        {Math.ceil(percentageScore)}%)
      </p>

      <p className="highscore"> The High Score is {highScore}</p>

      <button
        className="btn btn-ui"
        onClick={() => dispatch({ type: "start" })}
      >
        New Game
      </button>
    </>
  );
}

//export cannot have () - this implies a function call
export default FinishScreen;
