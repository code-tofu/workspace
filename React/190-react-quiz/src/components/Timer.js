import { useEffect } from "react";

function Timer({ time, dispatch }) {
  // useEffect here as timer should start on timer mount
  useEffect(
    function () {
      const id = setInterval(function () {
        dispatch({ type: "tick" });
      }, 1000);

      return () => clearInterval(id);
    },
    [dispatch]
  );
  return (
    <div className="timer">
      {Math.floor(time / 60)}:{String(time % 60).padStart(2, "0")}
    </div>
  );
}

// Timer causes a re-render for all child components of where the state is (in this case App)
export default Timer;
