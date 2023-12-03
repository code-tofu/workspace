import icons from '../../img/icons.svg';

export default class View{

    _data;
    //class way of declaring functions?
    renderSpinner() {
      console.log("spinner")
      console.log(this._parentElement)
  
      const markup = `
      <div class="spinner">
        <svg>
          <use href="${icons}.svg#icon-loader"></use>
        </svg>
      </div>
      `;
      this._clearInner();
      this._parentElement.insertAdjacentHTML('afterbegin', markup);
    }
  
    renderError(message = this._errorMessage) {
    console.log("renderError")
      const markup = `<div class="error">
      <div>
        <svg>
          <use href="src/img/${icons}.svg#icon-alert-triangle"></use>
        </svg>
      </div>
      <p>${message}</p>
      </div>
      `;
      this._clearInner();
      this._parentElement.insertAdjacentHTML('afterbegin', markup);
    }
  
    renderMessage(message) {
      const markup = 
        `
            <div class="message">
              <div>
                <svg>
                  <use href="src/img/icons.svg#icon-smile"></use>
                </svg>
              </div>
              <p>${message}</p>
            </div>
          </div>
      `;
      this._clearInner();
      this._parentElement.insertAdjacentHTML('afterbegin', markup);
      }

      render(data) { //adds the model data to the data field in the View class
        console.log('render');
        if(!data || (Array.isArray(data) && data.length ==0)) return this.renderError();
        this._data = data;
        const markup = this._generateMarkup();
        this._clearInner();
        this._parentElement.insertAdjacentHTML('afterbegin', markup);
      }

      /*
re-rendering the entire view is expensive - use an update method, but will only update text and attributes
not very good for a large DOM
*/
      update(data){
        console.log('update');
        // if(!data || (Array.isArray(data) && data.length ==0)) return this.renderError();
        this._data = data;
        const newMarkup = this._generateMarkup();
         const newDOM = document.createRange().createContextualFragment(newMarkup);
         //convert to array from nodelist
         const newElements = Array.from(newDOM.querySelectorAll("*"));
         const curElements = Array.from(this._parentElement.querySelectorAll("*"));
      
         newElements.forEach((newEl,i) => {
           //element node contains text node which has the value

           const curEl = curElements[i];
          // for text
           if(!newEl.isEqualNode(curEl) && newEl.firstChild?.nodeValue.trim() !== ""){
             curEl.textContent = newEl.textContent;
           }
           //for attribute (i.e. data for serving update)
           if(!newEl.isEqualNode(curEl)) {
            Array.from(newEl.attributes).forEach(attr => curEl.setAttribute(attr.name,attr.value))
          }
      
         })
      }
    
      _clearInner() {
        console.log('clear');
        this._parentElement.innerHTML = "";
        console.log(this._parentElement);
        console.log('clearAfter');
    
      }



}