<?php

/** @var \Laravel\Lumen\Routing\Router $router */

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It is a breeze. Simply tell Lumen the URIs it should respond to
| and give it the Closure to call when that URI is requested.
|
*/

$router->get('/', function () use ($router) {
    return $router->app->version();
});

$router->get('/api/picture', 'PictureController@index');
$router->get('/api/picture/{id}', 'PictureController@show');
$router->get('/api/picture/original/{id}', 'PictureController@original');
$router->get('/api/picture/processed/{id}', 'PictureController@processed');