#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"


Vec2* selected = NULL;
TransformedView tv;
Triangle triangle;
Sprite gc;

void Setup(AlxWindow* w){
	triangle = Triangle_New(
		(Vec2){ 10.0f,10.0f },
		(Vec2){ 10.0f,90.0f },
		(Vec2){ 90.0f,90.0f }
	);

	tv = TransformedView_Make(
		(Vec2){ GetWidth(),GetHeight() },
		(Vec2){ 0.0f,0.0f },
		(Vec2){ 0.01f,0.01f },
		(float)GetWidth() / (float)GetHeight()
	);
	gc = Sprite_New(GetWidth(),GetHeight());
}

void Update(AlxWindow* w){
	TransformedView_HandlePanZoom(&tv,w->Strokes,GetMouse());
	
	const float rs = 4.0f;
	const float r = TransformedView_ScreenWorldLX(&tv,rs);

	if(Stroke(ALX_MOUSE_L).PRESSED){
		selected = NULL;

		const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());

		for(int i = 0;i<3;i++){
			Vec2* p = (Vec2*)(&triangle) + i;
			const Vec2 d = Vec2_Sub(*p,m);
			
			if(Vec2_Mag2(d) < r * r){
				selected = p;
			}
		}
	}
	if(Stroke(ALX_MOUSE_L).DOWN){
		if(selected){
			const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
			*selected = m;
		}
	}

	Clear(LIGHT_BLUE);

	//const Vec2 p1 = TransformedView_WorldScreenPos(&tv,triangle.p1);
	//const Vec2 p2 = TransformedView_WorldScreenPos(&tv,triangle.p2);
	//const Vec2 p3 = TransformedView_WorldScreenPos(&tv,triangle.p3);
	
	Rect_RenderXX(gc.img,gc.w,gc.h,0.0f,0.0f,gc.w,gc.h,WHITE);

	Triangle_RenderX(gc.img,gc.w,gc.h,triangle.p1,triangle.p2,triangle.p3,GREEN);
	Triangle_RenderXWire(gc.img,gc.w,gc.h,triangle.p1,triangle.p2,triangle.p3,BLACK,1.0f);

	for(int i = 0;i<3;i++){
		Vec2* p = (Vec2*)(&triangle) + i;
		const Vec2 ps = TransformedView_WorldScreenPos(&tv,*p);
		
		//Circle_RenderX(WINDOW_STD_ARGS,ps,rs,RED);
	}

	const Vec2 pos = TransformedView_WorldScreenPos(&tv,(Vec2){ 0.0f,0.0f });
	const Vec2 len = TransformedView_WorldScreenLength(&tv,(Vec2){ gc.w,gc.h });
	Sprite_RenderResize(WINDOW_STD_ARGS,&gc,pos.x,pos.y,len.x,len.y);
}

void Delete(AlxWindow* w){
	
}

int main(){
    if(Create("3D Meshing",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}