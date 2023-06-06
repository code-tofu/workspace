import { Component, Input, OnInit } from '@angular/core';
import { CatalogueItem } from 'src/app/model/catalogue-item.model';

const imgURL: String =
  'https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/items/';
const imgType: String = '.png';

@Component({
  selector: 'app-cat-item',
  templateUrl: './cat-item.component.html',
  styleUrls: ['./cat-item.component.css'],
})
export class CatItemComponent implements OnInit {
  @Input()
  item!: CatalogueItem;
  imgsrc!: String;

  ngOnInit(): void {
    this.imgsrc = imgURL + this.item.nameID + imgType;
  }
}
