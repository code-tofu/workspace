import Button from "../../ui/Button";
import {useDispatch} from "react-redux"
import {increaseItemQuantity,decreaseItemQuantity} from "./cartSlice"

function UpdateItemQuantity({pizzaId, currentQuantity}){
    const dispatch = useDispatch()
    return (
        <div className="flex items-center gap-1 md:gap-3">
            <Button  type = "round" onClick={() =>dispatch(decreaseItemQuantity(pizzaId))}>-</Button>
            <span>{currentQuantity}</span>
            <Button  type = "round" onClick={() =>dispatch(increaseItemQuantity(pizzaId))}>+</Button>

        </div>
    )
}

export default UpdateItemQuantity;

/*
UpdateItemQuantity.jsx?t=1701604229811:31 Detected an action creator with type "cart/increaseItemQuantity" being dispatched. 
Make sure you're calling the action creator before dispatching, i.e. `dispatch(increaseItemQuantity())` instead of `dispatch(increaseItemQuantity)`. This is necessary even if the action has no payload.
*/