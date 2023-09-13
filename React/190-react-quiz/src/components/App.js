import { useEffect, useReducer } from "react";
import Header from "./Header";
import Main from "./Main";
import Loader from "./Loader";
import Error from "./Error";
import StartScreen from "./StartScreen";
import Question from "./Question";
import NextButton from "./NextButton";
import Progress from "./Progress";
import FinishScreen from "./FinishScreen";
import Timer from "./Timer";

export default function App() {
  const initialState = {
    questions: [],
    status: "loading", //'loading','error', 'ready', 'active','finished'
    index: 0, //current displayed question
    answer: null,
    score: 0,
    highScore: 0,
    time: 300,
  };

  function reducer(state, action) {
    switch (action.type) {
      case "dataReceived":
        return {
          ...state,
          questions: action.payload,
          status: "ready",
        };
      case "dataFailed":
        return {
          ...state,
          status: "error",
        };
      case "start":
        return {
          ...state,
          status: "active",
          answer: null,
          score: 0,
          index: 0,
          time: 300,
        };
      case "newAnswer":
        const currentQuestion = state.questions.at(state.index);
        return {
          ...state,
          answer: action.payload,
          score:
            currentQuestion.correctOption === action.payload
              ? state.score + currentQuestion.points
              : state.score,
        };
      //reducer should contain all the logic rather than at the event
      case "nextQuestion":
        return {
          ...state,
          index: state.index + 1,
          answer: null,
        };
      case "finishQuiz":
        return {
          ...state,
          status: "finished",
          highScore:
            state.score > state.highScore ? state.score : state.highScore,
        };
      case "tick":
        return {
          ...state,
          time: state.time - 1,
          status: state.time === 0 ? "finished" : state.status,
        };

      default:
        throw new Error("Invalid Action");
    }
  }

  //use Reducer returns state and dispatch
  //destructuring the state directly
  const [
    { questions, status, index, answer, score, highScore, time },
    dispatch,
  ] = useReducer(reducer, initialState);

  const numQuestions = questions.length;
  const maxPoints = questions.reduce((prev, curr) => prev + curr.points, 0);
  //loading data on mount
  useEffect(function () {
    fetch("http://localhost:8000/questions")
      .then((res) => res.json())
      .then((data) => dispatch({ type: "dataReceived", payload: data }))
      .catch((err) => dispatch({ type: "dataFailed" }));
  }, []);

  return (
    <div className="app">
      <Header />

      <Main>
        {status === "loading" && <Loader />}
        {status === "error" && <Error />}
        {status === "ready" && (
          <StartScreen numQuestions={numQuestions} dispatch={dispatch} />
        )}
        {status === "active" && (
          <>
            <Progress
              index={index}
              numQuestions={numQuestions}
              score={score}
              maxPoints={maxPoints}
              answer={answer}
            />
            <Question
              question={questions[index]}
              dispatch={dispatch}
              answer={answer}
            />
            <footer>
              <Timer time={time} dispatch={dispatch} />
              <NextButton
                dispatch={dispatch}
                answer={answer}
                numQuestions={numQuestions}
                index={index}
              />
            </footer>
          </>
        )}
        {status === "finished" && (
          <FinishScreen
            score={score}
            maxPoints={maxPoints}
            highScore={highScore}
            dispatch={dispatch}
          />
        )}
      </Main>
    </div>
  );
}
