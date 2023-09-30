/* eslint-disable react/prop-types */

import { useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { useAuth } from "../contexts/AuthContext";

function ProtectedRoute({ children }) {
  const { isAuthenticated } = useAuth();
  const navigate = useNavigate();

  useEffect(
    function () {
      if (!isAuthenticated) navigate("/");
    },
    [isAuthenticated, navigate]
  );

  //should return null if not children will try to access user during rendering before navigation happens (i.e. AppLayout tries to render.)
  return isAuthenticated ? children : null;
}

export default ProtectedRoute;
