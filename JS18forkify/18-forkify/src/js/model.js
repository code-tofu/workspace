import { API_URL, PAGE_SIZE } from './config.js';
import { getJSON } from './helper.js';

export const state = {
  recipe: {},
  search: {
    query: '',
    results: {},
    page:1,
  },
  bookmarks: []
};

export const addBookmark = function(recipe){
	state.bookmarks.push(recipe);
	if(recipe.id === state.recipe.id)
		state.recipe.bookmarked = true;
	//create new bookmarked property
  console.log(state.bookmarks)
}

export const deleteBookmark = function(id){
	const index = state.bookmarks.findIndex(el => el.id ===id)
	state.bookmarks.splice(index,1);

	if (id === state.recipe.id) state.recipe.bookmarked=false;
};

export const loadRecipe = async function (id) {
  try {
    console.log('loadRecipe');
    const data = await getJSON(`${API_URL}/${id}`);
    const { recipe } = data.data;
    state.recipe = {
      id: recipe.id,
      title: recipe.title,
      publisher: recipe.publisher,
      sourceUrl: recipe.source_url,
      image: recipe.image_url,
      servings: recipe.servings,
      cookingTime: recipe.cooking_time,
      ingredients: recipe.ingredients,
    };

    if(state.bookmarks.some(bookmark => bookmark.id ===id)){
      state.recipe.bookmarked = true;
    } else state.recipe.bookmarked = false;
    console.log(state.recipe);
  } catch (err) {
    throw err;
  }
};

export const loadSearchResults = async function (query) {
  try {
    console.log("loadSearch:",query);
    state.search.query = query;
    const data = await getJSON(`${API_URL}?search=${query}`);
    state.search.results = data.data.recipes.map(recipe => {
      return {
        id: recipe.id,
        title: recipe.title,
        publisher: recipe.publisher,
        sourceUrl: recipe.source_url,
        image: recipe.image_url,
      };
    });
    console.log(state.search.results)
    state.search.page = 1;
  } catch (err) {
    throw err;
  }
};



export const getSearchResultsPage = function(page = state.search.page){
  state.search.page = page;
	const start = (page - 1) * PAGE_SIZE ;
	const end = page * PAGE_SIZE;
  console.log("page",page,"start",start,"end",end)
	return state.search.results.slice(start,end)
}

export const updateServings = function(newServings) {
  state.recipe.ingredients.forEach(ing => {
    ing.quantity = ing.quantity * newServings/state.recipe.servings;
  })
  state.recipe.servings = newServings;
}

