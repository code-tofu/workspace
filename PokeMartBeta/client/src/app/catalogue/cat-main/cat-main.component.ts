import { HttpClient } from '@angular/common/http';
import { Component, OnInit, inject } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Observable } from 'rxjs';
import { CatalogueItem } from 'src/app/model/catalogue-item.model';
import { CatalogueService } from 'src/app/services/catalogue.service';

const perPage: number = 10;

@Component({
  selector: 'app-cat-main',
  templateUrl: './cat-main.component.html',
  styleUrls: ['./cat-main.component.css'],
})
export class CatMainComponent implements OnInit {
  catalogue$!: Observable<CatalogueItem[]>;
  category!: string;

  catSvc = inject(CatalogueService);
  actRoute = inject(ActivatedRoute);
  page: number = 0;

  ngOnInit(): void {
    if (this.actRoute.snapshot.url[0]) {
      //TODO: NOT CLEAN CODE
      if (this.actRoute.snapshot.url[0].path == 'category') {
        this.catalogue$ = this.catSvc.getCataloguebyCategory(
          this.actRoute.snapshot.params['category']
        );
        this.category = this.actRoute.snapshot.params['category'];
      }
    } else {
      this.catalogue$ = this.catSvc.getCatalogue(this.page * perPage);
    }
  }

  increasePage() {
    this.page += 1;
  }
  decreasePage() {
    this.page -= 1;
  }
}
