function Progress({ index, numQuestions, score, maxPoints, answer }) {
  return (
    <header className="progress">
      <progress max={numQuestions} value={index + Number(answer !== null)} />
      {/* using truthy values */}
      <p>
        Question <strong>{index + 1}</strong>/ {numQuestions}
      </p>
      <p>
        Points: <strong>{score}</strong>/{maxPoints}
      </p>
    </header>
  );
}
export default Progress;
