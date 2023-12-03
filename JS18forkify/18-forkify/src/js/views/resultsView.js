import icons from '../../img/icons.svg';
import View from './view.js'

class ResultsView extends View{
    _parentElement = document.querySelector('.results'); //for easier selection
    _errorMessage = "Results View Error: No Results  for this Query"


    _generateMarkup() {
        return this._data.map(item => this._generatePreview(item)).join('');
    }

    _generatePreview(item){
    	const id = window.location.hash.slice(1);
      // console.log("id",item.id,id);
        return `
        <li class="preview">
        <a class="preview__link ${ item.id === id ? 'preview__link--active' : ""}" href="#${item.id}">
          <figure class="preview__fig">
            <img src="${item.image}" alt="${item.title}" />
          </figure>
          <div class="preview__data">
            <h4 class="preview__title">${item.title}</h4>
            <p class="preview__publisher">${item.publisher}</p>
          </div>
        </a>
      </li>
      `;
    }
}

export default new ResultsView();