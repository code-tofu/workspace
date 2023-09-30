/*eslint no-unused-vars: [1, { "vars": "all" }]*/

import { BrowserRouter, Routes, Route, Navigate } from "react-router-dom";
import Product from "./pages/Product";
import Pricing from "./pages/Pricing";
import Homepage from "./pages/Homepage";
import Login from "./pages/Login";
import NotFound from "./pages/NotFound";
import AppLayout from "./pages/AppLayout";
import CityList from "./components/CityList";

import CountryList from "./components/CountryList";
import City from "./components/City";
import Form from "./components/Form";
import { CitiesProvider } from "./contexts/CitiesContext";
import { AuthProvider } from "./contexts/AuthContext";
import ProtectedRoute from "./pages/ProtectedRoute";

export default function App() {
  // MOVED TO CONTEXT
  //   const [cities, setCities] = useState([]);
  //   const [isLoading, setIsLoading] = useState(false);

  //   useEffect(function () {
  //     async function fetchCities() {
  //       try {
  //         setIsLoading(true);
  //         const res = await fetch(citiesURL);
  //         const data = await res.json();
  //         setCities(data);
  //       } catch {
  //         alert("Cities Server Error");
  //       } finally {
  //         setIsLoading(false);
  //       }
  //     }
  //     //remember to call the function in useEffect
  //     fetchCities();
  //   }, []);

  //   return (
  //     <BrowserRouter>
  //       <Routes>
  //         <Route index element={<Homepage />} />
  //         <Route path="product" element={<Product />} />
  //         <Route path="pricing" element={<Pricing />} />
  //         <Route path="login" element={<Login />} />
  //         <Route path="app" element={<AppLayout />}>
  //           <Route index element={<Navigate replace to="cities" />} />
  //           <Route
  //             path="cities"
  //             element={<CityList cities={cities} isLoading={isLoading} />}
  //           />
  //           <Route path="cities/:id" city element={<City />} />
  //           <Route
  //             path="countries"
  //             element={<CountryList cities={cities} isLoading={isLoading} />}
  //           />
  //           <Route path="countries" element={<CountryList />} />
  //           <Route path="form" element={<Form />} />
  //         </Route>
  //         <Route path="*" element={<NotFound />} />
  //       </Routes>
  //     </BrowserRouter>
  //   );

  return (
    <AuthProvider>
      <CitiesProvider>
        <BrowserRouter>
          <Routes>
            <Route index element={<Homepage />} />
            <Route path="product" element={<Product />} />
            <Route path="pricing" element={<Pricing />} />
            <Route path="login" element={<Login />} />
            <Route
              path="app"
              element={
                <ProtectedRoute>
                  <AppLayout />
                </ProtectedRoute>
              }
            >
              <Route index element={<Navigate replace to="cities" />} />
              <Route path="cities" element={<CityList />} />
              <Route path="cities/:id" city element={<City />} />
              <Route path="countries" element={<CountryList />} />
              <Route path="countries" element={<CountryList />} />
              <Route path="form" element={<Form />} />
            </Route>
            <Route path="*" element={<NotFound />} />
          </Routes>
        </BrowserRouter>
      </CitiesProvider>
    </AuthProvider>
  );
}
