import{createSlice} from "@reduxjs/toolkit"

const initialState ={
    cart: [],
}; //cart of items, because the rest of the properties like price can be derived
//pizzaIDm nanem qty, unitprice,totalprice (qty*unitprice)

const cartSlice = createSlice({
    name: 'cart',
    initialState,
    reducers:{
        addItem(state,action){
            //payload is whatever we pass into the action creator when we dispatch an action
            //payload = newItem
            state.cart.push(action.payload);
        },
        deleteItem(state,action){
            //payload  = pizzaId
            state.cart = state.cart.filter((item=>item.pizzaId !== action.payload));
            console.log(state.cart);

        },
        increaseItemQuantity(state,action){
            const item = state.cart.find(item => item.pizzaId === action.payload);
            item.quantity++;
            item.totalPrice = item.quantity * item.unitPrice;
        },
        decreaseItemQuantity(state,action){
            const item = state.cart.find(item => item.pizzaId === action.payload);
            // if (item.quantity===0) return;
            // instead of deleting item, use caseReducers to call
            if(item.quantity ===0) cartSlice.caseReducers.deleteItem(state,action);
            item.quantity--;
            item.totalPrice = item.quantity * item.unitPrice;
        },
        clearCart(state){
            //action i.e. payload not required
            state.cart = [];
        }

    }
})

export const {addItem,deleteItem,increaseItemQuantity,decreaseItemQuantity,clearCart} = cartSlice.actions;
export default cartSlice.reducer;

export const getTotalCartQuantity = (state => state.cart.cart.reduce((sum,item)=> sum + item.quantity,0));

export const getTotalCartPrice = (state => state.cart.cart.reduce((sum,item)=> sum + item.totalPrice,0));

export const getCart = (state => state.cart.cart)

// creating a selector that takes in an id
export const getCurrentQuantity = (id)=> (state => state.cart.cart.find(item => item.pizzaId === id)?.quantity ?? 0);