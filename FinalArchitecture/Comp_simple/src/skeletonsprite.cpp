#include "../stdafx.h"
#include "../include/skeletonsprite.h"
#include "../include/bone.h"
#include "../include/bonedata.h"
#include "../include/glinclude.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/skeletondata.h"
#include "../include/string.h"

SkeletonSprite::SkeletonSprite(const String& filename) : Sprite(NULL) {
	// Cargamos los datos del XML
	SkeletonData* data = new SkeletonData(filename);

    root = new Bone("world", NULL, 0, 0, 0, 0);

	// Generamos huesos
    for ( uint32 i = 0; i < data->GetBoneDatas().Size(); i++ ) {
		// Obtenemos hueso
        const BoneData& boneData = data->GetBoneDatas()[i];
		
		// Obtenemos padre del hueso
        Bone* parent = root;
        if ( boneData.GetParentName() != "world" )
            parent = root->FindChild(boneData.GetParentName());

		// Obtenemos imagen
        Image* newImage = ResourceManager::Instance().LoadImage(filename.ExtractDir() + "/" + boneData.GetImageFilename());

		// Creamos hueso
        Bone bone(boneData.GetId(), newImage, boneData.GetPivotX(), boneData.GetPivotY(), boneData.GetHandleX(), boneData.GetHandleY());

		// Aniadimos frames
        for ( uint32 j = 0; j < boneData.GetFrames().Size(); j++ )
            bone.AddFrame(boneData.GetFrames()[j]);

		// Aniadimos hueso
		parent->AddChild(bone);	
	}

	// Establecemos el rango de la animacion
    const Bone* bone = root->GetChild(0);
	int32 lastframe = 0;
	for ( uint32 index = 0; index < bone->CountFrames(); index++ ) {
        lastframe = max(lastframe, bone->GetFrame(index)->GetId());
	}
	SetFrameRange(0, static_cast<uint16>(lastframe));

	// Eliminamos los datos cargados del XML
	delete data;
}

SkeletonSprite::~SkeletonSprite() {
	delete root;
}

void SkeletonSprite::Update(double elapsed, Map* map) {
	// Llamamos al metodo padre
	Sprite::Update(elapsed, map);

	root->Update(GetCurrentFrame());
}

void SkeletonSprite::Render() const {
	Renderer::Instance().SetBlendMode(GetBlendMode());
	Renderer::Instance().SetColor(GetRed(), GetGreen(), GetBlue(), GetAlpha());
	
	glPushMatrix();
	glTranslated(GetX(), GetY(), 0);
	root->Render();
	glPopMatrix();
}
