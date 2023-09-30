/*eslint no-unused-vars: [1, { "vars": "all" }]*/
/* eslint-disable react/prop-types */
import { createContext, useContext, useReducer } from "react";
import { useState, useEffect } from "react";

const CitiesContext = createContext();

const citiesURL = "http://localhost:8888/cities";

const initialState = {
  cities: [],
  isLoading: false,
  currentCity: {},
  error: "",
};

function useCities() {
  const context = useContext(CitiesContext);
  if (context === undefined)
    throw new Error("Cities Context used outside cities provider");
  return context;
}

function reducer(state, action) {
  switch (action.type) {
    case "cities/loading": //react practice
      return { ...state, isLoading: true };
    case "cities/loaded": //react practice
      return { ...state, isLoading: false, cities: action.payload };
    case "city/created":
      return {
        ...state,
        isLoading: false,
        cities: [...CitiesContext, action.payload],
      };
    case "city/deleted":
      return {
        ...state,
        isLoading: false,
        cites: state.cities.filter((city) => city.id !== action.payload),
      };

    case "city/loaded":
      return { ...state, isLoading: false, currentCity: action.payload };
    case "error":
      return { ...state, isLoading: false, error: action.payload };
    default:
      throw new Error("Unknown Action");
  }
}

function CitiesProvider({ children }) {
  //   const [cities, setCities] = useState([]);
  //   const [isLoading, setIsLoading] = useState(false);
  //   const [currentCity, setCurrentCity] = useState({});
  const [{ cities, isLoading, currentCity }, dispatch] = useReducer(
    reducer,
    initialState
  );

  useEffect(function () {
    async function fetchCities() {
      dispatch({ type: "cities/loading" });
      try {
        // setIsLoading(true);
        const res = await fetch(citiesURL);
        const data = await res.json();
        // setCities(data);
        dispatch({ type: "cities/loaded", payload: data });
      } catch {
        dispatch({ type: "error", payload: "Cities Server Error" });
        // alert("Cities Server Error");
      }
      //   } finally {
      //     setIsLoading(false);
      //   }
    }
    //remember to call the function in useEffect
    fetchCities();
  }, []);

  async function getCity(id) {
    dispatch({ type: "cities/loading" });
    try {
      //   setIsLoading(true);
      const res = await fetch(`${citiesURL}/${id}`);
      const data = await res.json();
      dispatch({ type: "city/loaded", payload: data });
      //   setCurrentCity(data);
      //   console.info(currentCity);
    } catch {
      dispatch({ type: "error", payload: "Cities Server Error" });
      //   alert("Cities Server Error");
    }
    // } finally {
    //   setIsLoading(false);
    // }
  }

  async function createCity(newCity) {
    dispatch({ type: "cities/loading" });
    try {
      //   setIsLoading(true);
      const res = await fetch(`${citiesURL}/cities`, {
        method: "POST",
        body: JSON.stringify(newCity),
        headers: { "Content-Type": "application/json" },
      });
      const data = await res.json();
      //   setCities((cities) => [...cities, data]);
      dispatch({ type: "city/created", payload: data });
    } catch {
      dispatch({ type: "error", payload: "Cities Server Error" });

      //   alert("Cities Server Error");
    }
    // } finally {
    //   setIsLoading(false);
    // }
  }

  async function deleteCity(id) {
    dispatch({ type: "cities/loading" });
    try {
      //   setIsLoading(true);
      const res = await fetch(`${citiesURL}/cities/${id}`, {
        method: "DELETE",
      });
      dispatch({ type: "city/deleted", payload: id });
      //   setCities((cities) => cities.filter((city) => city.id !== id));
    } catch {
      dispatch({
        type: "error",
        payload: "Deleting City in Cities Server Error",
      });
      //   alert("Deleting City in Cities Server Error");
    }
    // } finally {
    //   setIsLoading(false);
    // }
  }

  return (
    <CitiesContext.Provider
      value={{
        cities,
        isLoading,
        currentCity,
        getCity,
        deleteCity,
        createCity,
      }}
    >
      {children}
    </CitiesContext.Provider>
  );
}

export { CitiesProvider, useCities };
