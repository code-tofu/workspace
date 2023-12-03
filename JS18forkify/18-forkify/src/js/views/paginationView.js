import icons from '../../img/icons.svg';
import View from './view.js'
import { PAGE_SIZE } from '../config.js';

class PaginationView extends View {
	_parentElement = document.querySelector('.pagination');

  addHandlerClick(handler){
    //eventdelegation
    this._parentElement.addEventListener('click',function(e){
      const btn = e.target.closest('.btn--inline');
      if(!btn) return;
      const targetPage = +btn.dataset.goto;
      console.log("loadPage",targetPage)
      handler(targetPage);
    })
  }

	_generateMarkup(){
		const numPages = Math.ceil(this._data.results.length / PAGE_SIZE);
        const currentPage = this._data.page;
        if( currentPage === 1 && numPages > 1){
          console.log("case1")
            return `
             <button data-goto="${currentPage+1}" class="btn--inline pagination__btn--next">
               <span>Page ${currentPage+1}</span>
               <svg class="search__icon">
                 <use href="${icons}#icon-arrow-right"></use>
               </svg>
             </button>
           `
   
        }
        if(currentPage === numPages && numPages > 1){
          console.log("case2")
            return `
           <button data-goto="${currentPage-1}" class="btn--inline pagination__btn--prev">
           <svg class="search__icon">
             <use href="${icons}#icon-arrow-left"></use>
           </svg>
           <span>Page ${currentPage-1}</span>
             </button>
           `
        }
        if(currentPage < numPages){
          console.log("case3")
            return `
           <button data-goto="${currentPage-1}" class="btn--inline pagination__btn--prev">
           <svg class="search__icon">
             <use href="${icons}#icon-arrow-left"></use>
           </svg>
           <span>Page ${currentPage-1}</span>
             </button>

               <button data-goto="${currentPage+1}" class="btn--inline pagination__btn--next">
               <span>Page ${currentPage+1}</span>
               <svg class="search__icon">
                 <use href="${icons}#icon-arrow-right"></use>
               </svg>
             </button>
           `
        }
        //default
        console.log("case4")
        return '';
	}

}

export default new PaginationView();