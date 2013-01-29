#include <math.h>
#include "GameActionUtilities.h"
#include "BubblesAnimator.h"
#include "AnimatorHolder.h"
#include "MemoryManage.h"
#include "CollisionChecker.h"
#include "AnimationsParser.h"
#include "AnimationFilmHolder.h"
#include "Terrain.h"


/////////////////////////////static functios
static int getClosestIndexFromPath(int x, int y, const std::vector<PathEntry>& path){
	double minDistance=1024;
	int index=-1;
	for(unsigned int i=0; i<path.size(); ++i){
		double distance = sqrt( pow( double(path[i].x - x), 2 ) + pow( double(path[i].y - y), 2 ) );
		if( distance < minDistance ){
			minDistance = distance;
			index=i;
		}
	}

	return index;
}

static std::vector<PathEntry> getPath(const int index, const std::vector<PathEntry>& constPath){
	std::vector<PathEntry> path;

	for(unsigned int i = index; i<constPath.size()-1; ++i){
		PathEntry entry;
		entry.x = constPath[i+1].x - constPath[i].x;
		entry.y = constPath[i+1].y - constPath[i].y;
		entry.delay =  constPath[i].delay;
		entry.frame = constPath[i].frame;
		path.push_back(entry);
	}
	return path;
}

//////////////////////////////BubBubbleBlastOffAnimator

BubBubbleBlastOffAnimator::BubBubbleBlastOffAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void BubBubbleBlastOffAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubBubbleBlastOffAnimator * _this = (BubBubbleBlastOffAnimator*)args;
	DASSERT( anim==_this );
	DASSERT( _this->GetAnimation() && _this->GetSprite() );
	
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	
	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("Bubbles");
	int startIndex = getClosestIndexFromPath( _this->GetSprite()->GetX(),  _this->GetSprite()->GetY(), mpa->GetPath() );
	std::vector<PathEntry> pathEntry = getPath(startIndex, mpa->GetPath());
	Sprite *sprite=new Sprite(
								mpa->GetPath()[startIndex].x,
								mpa->GetPath()[startIndex].y,
								false,
								AnimationFilmHolder::GetFilm( "BubBubble" ), 
								Terrain::GetActionLayer(), 
								true
							);
	mpa->SetPath( pathEntry );
	BubBubbleAnimator *bbar=new BubBubbleAnimator();
	
	std::vector<Animator*> bubbles = AnimatorHolder::GetAnimators(bubBubbleAnimator_t);
	for(unsigned int i=0; i<bubbles.size(); ++i){
		CollisionChecker::Register(sprite, ( (BubBubbleAnimator*)bubbles[i] )->GetSprite(), (void*)bbar, BubBubbleAnimator::OnCollisionWithBubble);
	}

	START_ANIMATOR(bbar, sprite, mpa, GetGameTime() );
	DESTROY_ANIMATOR( _this );
}

/////////////////////////////BubBubbleAnimator

BubBubbleAnimator::BubBubbleAnimator(){
	this->SetOnFinish( OnFinishCallback, (void*)this );
}

void BubBubbleAnimator::OnFinishCallback(Animator* anim, void* args){
	DASSERT( anim && args);
	BubBubbleAnimator * _this = (BubBubbleAnimator*)args;
	DASSERT( anim==_this );
	REMOVE_FROM_ACTION_ANIMATOR( _this );
	DESTROY_ANIMATOR( _this );
}

void BubBubbleAnimator::OnCollisionWithBubble(Sprite *spr1, Sprite *spr2, void *args){
	DASSERT( args );
	BubBubbleAnimator* m = (BubBubbleAnimator*)args;
	if(spr1->GetX()>spr2->GetX()){
		spr1->Move( 1, 0 );
		
	}else{
		spr1->Move( -1, 0 );
	}
	if(spr1->GetY()>spr2->GetY()){
		spr1->Move( 0, 1 );
	}else{
		spr1->Move( 0, -1 );
	}
}