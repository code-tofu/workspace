import Option from "./Options";

function Question({ question, dispatch, answer }) {
  return (
    <div>
      <h4>{question.question}</h4>
      <Option
        options={question.options}
        dispatch={dispatch}
        answer={answer}
        correct={question.correctOption}
      />
    </div>
  );
}

export default Question;
