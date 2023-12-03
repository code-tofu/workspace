import * as model from './model.js'
import recipeView from './views/recipeView.js'
import searchView from './views/searchView.js'
import resultsView from './views/resultsView.js';
import paginationView from './views/paginationView.js';
import bookmarksView from './views/bookmarksView.js';


// import 'core/js/stable';
// import 'regenerator-runtime/runtime'
// console.log(icons)

// const recipeContainer = document.querySelector('.recipe');

// https://forkify-api.herokuapp.com/v2


//parcel hot loading
// if(module.hot) {
//   module.hot.accept();
// }

const controlRecipes = async function () {
  try {

    const id = window.location.hash.slice(1);
    console.log(id);
    if(!id) return; //guard clause
    recipeView.renderSpinner(); //no need to pass in parent element
    resultsView.update(model.getSearchResultsPage());
    bookmarksView.update(model.state.bookmarks)
    await model.loadRecipe(id); //since state update is a promise - await the completion of the function
    const {recipe} = model.state;
    recipeView.render(model.state.recipe);  
  } catch (err) {
    recipeView.renderError();
  }
};

const controlSearchRecipes = async function(){
  try{
    resultsView.renderSpinner();
    const query = searchView.getQuery();
    if(!query) return;
    await model.loadSearchResults(query);
    // searchView.clearInput();
    resultsView.render(model.getSearchResultsPage())
    paginationView.render(model.state.search);
  }catch (err){
    console.log(err);
  }
} 

const controlPagination = function(targetPage){
  
  console.log("controlPage",targetPage)
  resultsView.render(model.getSearchResultsPage(targetPage))
  paginationView.render(model.state.search);
}

//controllers same as event handlers
const controlServings = function(newServing){
  console.log("controlServings")
	//update underlying data in state and the view
	model.updateServings(newServing)
	//rerender the whole recipe which servings and ing quanity has been modified
	recipeView.update(model.state.recipe);
}

const controlAddBookmark = function (){
  console.log("addRecipe",model.state.recipe)
  if(!model.state.recipe.bookmarked){
    model.addBookmark(model.state.recipe);
  } else {
    model.deleteBookmark(model.state.recipe.id)
  }
  recipeView.update(model.state.recipe);
  bookmarksView.render(model.state.bookmarks);
}


const init = function(){
  console.log("init")
  //publisher-subscriber pattern
  recipeView.addHandlerRender(controlRecipes);
  searchView.addHandlerSearch(controlSearchRecipes);
  paginationView.addHandlerClick(controlPagination);
  recipeView.addHandlerUpdateServings(controlServings);
  recipeView.addHandlerAddBookmark(controlAddBookmark)
}
init();

// controlRecipes(); //already called in init
