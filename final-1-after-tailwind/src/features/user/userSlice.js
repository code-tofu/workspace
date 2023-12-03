import {createSlice} from "@reduxjs/toolkit"
import {getAddress} from '../../services/apiGeocoding';
import {createAsyncThunk} from '@reduxjs/toolkit'


const initialState = {
  username:'',
  status:'idle',
  position:{},
  address:'',
  error:''
};

const fetchAddress = createAsyncThunk('user/fetchAddress', async function(){
  // 1) We get the user's geolocation position
  const positionObj = await getPosition();
  const position = {
    latitude: positionObj.coords.latitude,
    longitude: positionObj.coords.longitude,
  };

  // 2) Then we use a reverse geocoding API to get a description of the user's address, so we can display it the order form, so that the user can correct it if wrong
  const addressObj = await getAddress(position);
  const address = `${addressObj?.locality}, ${addressObj?.city} ${addressObj?.postcode}, ${addressObj?.countryName}`;

  // 3) Then we return an object with the data that we are interested in
  return { position, address };
}
)

// create a slice for user of the global UI state
const userSlice = createSlice({
  name: 'user', //this is a named variable i.e. name of the slice
  initialState,
  reducers:{
    updateName(state,action){
      state.username = action.payload;
    }
  },
  //called extraReducers
  extraReducers: (builder => builder
    .addCase(fetchAddress.pending, (state,action) => {state.status = 'loading'
    console.log("thunk pending")
  })
    .addCase(fetchAddress.fulfilled, (state,action) => {
      state.position = action.payload.position;
      state.address = action.payload.address;
      state.status = 'idle';
    })
    .addCase(fetchAddress.rejected, (state,action) => {
      state.status = 'error';
      state.error = action.error.message
    })),
});


export const {updateName} = userSlice.actions; //gives us action creators

//export reducer to create store
export default userSlice.reducer;

function getPosition() {
  return new Promise(function (resolve, reject) {
    navigator.geolocation.getCurrentPosition(resolve, reject);
  });
}

//redux is synchronous hence you cannot call async functions from redux reducer - hence use thunks
//thunk is a middleware between dispatch and reducer

/* replaced with thunks
async function fetchAddress() {
  // 1) We get the user's geolocation position
  const positionObj = await getPosition();
  const position = {
    latitude: positionObj.coords.latitude,
    longitude: positionObj.coords.longitude,
  };

  // 2) Then we use a reverse geocoding API to get a description of the user's address, so we can display it the order form, so that the user can correct it if wrong
  const addressObj = await getAddress(position);
  const address = `${addressObj?.locality}, ${addressObj?.city} ${addressObj?.postcode}, ${addressObj?.countryName}`;

  // 3) Then we return an object with the data that we are interested in
  return { position, address };
}
*/

//can use toolkit or manually (see section on thunks)
//prefeix getAddress should be reserved for selectors


