# Backend

This project was generated with [Angular CLI](https://github.com/angular/angular-cli).

## Development

There are detailed instructions for developers in the MythTV wiki at [Web Application Development](https://www.mythtv.org/wiki/Web_Application_Development).

## Development server

- Startup a copy of mythbackend, as the local dev server will proxy api calls to it.
- Edit `src/proxy.conf.js` and ensure the `target` is set to point to the backend started in the previous step.
- Run `ng serve` for a dev server. Navigate to `http://localhost:4200/`. The app will automatically reload if you change any of the source files.

## Code scaffolding

Run `ng generate component component-name` to generate a new component. You can also use `ng generate directive|pipe|service|class|guard|interface|enum|module`.

## Build

Run `npm run-script build` to build the project. The build artifacts will be stored in the `../apps/backend` directory.
These should be committed, so that the backend web app does not need rebuilding at build time.

## Running unit tests

Run `ng test` to execute the unit tests via [Karma](https://karma-runner.github.io).

## Running end-to-end tests

Run `ng e2e` to execute the end-to-end tests via a platform of your choice. To use this command, you need to first add a package that implements end-to-end testing capabilities.

## Further help

To get more help on the Angular CLI use `ng help` or go check out the [Angular CLI Overview and Command Reference](https://angular.io/cli) page.
