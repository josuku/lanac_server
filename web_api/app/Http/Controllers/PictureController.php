<?php

namespace App\Http\Controllers;
use Laravel\Lumen\Routing\Controller as BaseController;
use Illuminate\Http\Request;
use App\Models\PictureModel;

class PictureController extends BaseController{
    public function index(){
        $data = PictureModel::all();
        return response($data);
    }

    public function show($id){
        $data = PictureModel::where('id', $id)->get();

        if (count($data) > 0) {
            return response ($data);
        } 
        else {
            return response('Picture not found');
        }
    }

    public function original($id){
        $data = PictureModel::where('id', $id)->get();
        if (count($data) > 0) {
            $image = file_get_contents($data[0]->original_path);
            return response($image)->header('Content-Type','image/png');
        } 
        else {
            return response('Picture not found');
        }
    }

    public function processed($id){
        $data = PictureModel::where('id', $id)->get();

        if (count($data) > 0) {
            $image = file_get_contents($data[0]->processed_path);
            return response($image)->header('Content-Type','image/png');
        } 
        else {
            return response('Picture not found');
        }
    }
}
