import Header from "./Header";
import CartOverview from "../features/cart/CartOverview"
import {Outlet, useNavigation} from "react-router-dom"
import LoadingSpinner from "./LoadingSpinner";

function AppLayout() {
    const navigation = useNavigation;
    const isLoading = navigation.state === "loading";
    //loader is an oerlay

    return (<div className="layout">
        {isLoading && <LoadingSpinner/>}
    <Header/>
    <main>
            <Outlet />
        </main>
        <CartOverview/>
    </div>);
}

export default AppLayout;