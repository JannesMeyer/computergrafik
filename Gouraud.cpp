#include "Gouraud.h"


Gouraud::Gouraud()
{
	
	//void Gouraud::glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz );
	////Zeichenroutine
	//glBegin(GL_TRIANGLES);
	//	for (j=0;j<object.polygons_qty;j++)
	//	{
	//		//----------------- FIRST VERTEX -----------------
	//		//Normal coordinates of the first vertex
	//		glNormal3f( object.normal[ object.polygon[j].a ].x,
 //                 object.normal[ object.polygon[j].a ].y,
 //                 object.normal[ object.polygon[j].a ].z);
	//		// Texture coordinates of the first vertex
	//		glTexCoord2f( object.mapcoord[ object.polygon[j].a ].u,
 //                   object.mapcoord[ object.polygon[j].a ].v);
	//		// Coordinates of the first vertex
	//		glVertex3f( object.vertex[ object.polygon[j].a ].x,
 //                 object.vertex[ object.polygon[j].a ].y,
 //                 object.vertex[ object.polygon[j].a ].z);

	//		//----------------- SECOND VERTEX -----------------
	//		//Normal coordinates of the second vertex
	//		glNormal3f( object.normal[ object.polygon[j].b ].x,
 //                 object.normal[ object.polygon[j].b ].y,
 //                 object.normal[ object.polygon[j].b ].z);
	//		// Texture coordinates of the second vertex
	//		glTexCoord2f( object.mapcoord[ object.polygon[j].b ].u,
 //                   object.mapcoord[ object.polygon[j].b ].v);
	//		// Coordinates of the second vertex
	//		glVertex3f( object.vertex[ object.polygon[j].b ].x,
 //                 object.vertex[ object.polygon[j].b ].y,
 //                 object.vertex[ object.polygon[j].b ].z);

	//		//----------------- THIRD VERTEX -----------------
	//		//Normal coordinates of the third vertex
	//		glNormal3f( object.normal[ object.polygon[j].c ].x,
 //                 object.normal[ object.polygon[j].c ].y,
 //                 object.normal[ object.polygon[j].c ].z);
	//		// Texture coordinates of the third vertex
	//		glTexCoord2f( object.mapcoord[ object.polygon[j].c ].u,
 //                   object.mapcoord[ object.polygon[j].c ].v);
	//		// Coordinates of the Third vertex
	//		glVertex3f( object.vertex[ object.polygon[j].c ].x,
 //                 object.vertex[ object.polygon[j].c ].y,
 //                 object.vertex[ object.polygon[j].c ].z);
	//}
	//glEnd();
}
//
//void Gouraud::ObjCalcNormals(obj_type_ptr p_object)
//{
//	// Unterstützungsvariablen
//	int i;
//	p3d_type l_vect1,l_vect2,l_vect3,l_vect_b1,l_vect_b2,l_normal;
//	int l_connections_qty[MAX_VERTICES];
//
//	//alle die Normalen der Eckpunkte setzten
//	for (i=0; i<p_object->vertices_qty; i++) {
//		p_object->normal[i].x = 0.0;
//		p_object->normal[i].y = 0.0;
//		p_object->normal[i].z = 0.0;
//		l_connections_qty[i]=0;
//	}
//
//	//für jedes Polygon
//	for (i=0; i<p_object->polygons_qty; i++)
//	{
//		l_vect1.x = p_object->vertex[p_object->polygon[i].a].x;
//		l_vect1.y = p_object->vertex[p_object->polygon[i].a].y;
//		l_vect1.z = p_object->vertex[p_object->polygon[i].a].z;
//		l_vect2.x = p_object->vertex[p_object->polygon[i].b].x;
//		l_vect2.y = p_object->vertex[p_object->polygon[i].b].y;
//		l_vect2.z = p_object->vertex[p_object->polygon[i].b].z;
//		l_vect3.x = p_object->vertex[p_object->polygon[i].c].x;
//		l_vect3.y = p_object->vertex[p_object->polygon[i].c].y;
//		l_vect3.z = p_object->vertex[p_object->polygon[i].c].z;
//
//		// erstellen zwei Koplanarvektoren mit Hilfe zweier Seiten des Polygons
//		VectCreate (&l_vect1, &l_vect2, &l_vect_b1);
//		VectCreate (&l_vect1, &l_vect3, &l_vect_b2);
//
//		//Berechnung des Vektorproduktes zwischen diesen Vektoren
//		VectDotProduct (&l_vect_b1, &l_vect_b2, &l_normal);
//
//		//für jede gemeinsame Ecke dieses Polygons erhöht man die Anzahl der Verbindungen
//		l_connections_qty[p_object->polygon[i].a]+=1;
//		l_connections_qty[p_object->polygon[i].b]+=1;
//		l_connections_qty[p_object->polygon[i].c]+=1;
//
//		 //......und füge die Polygonnormalen
//		 p_object->normal[p_object->polygon[i].a].x+=l_normal.x;
//		 p_object->normal[p_object->polygon[i].a].y+=l_normal.y;
//		 p_object->normal[p_object->polygon[i].a].z+=l_normal.z;
//		 p_object->normal[p_object->polygon[i].b].x+=l_normal.x;
//		 p_object->normal[p_object->polygon[i].b].y+=l_normal.y;
//		 p_object->normal[p_object->polygon[i].b].z+=l_normal.z;
//		 p_object->normal[p_object->polygon[i].c].x+=l_normal.x;
//		 p_object->normal[p_object->polygon[i].c].y+=l_normal.y;
//		 p_object->normal[p_object->polygon[i].c].z+=l_normal.z; 
//	  } 
//
//	// Durchschnitt Polygonnormalen für die Eckennormalen
//	for (i=0; i<p_object->vertices_qty; i++)
//	{
//		if (l_connections_qty[i]>0)
//		{
//			p_object->normal[i].x /= l_connections_qty[i];
//			p_object->normal[i].y /= l_connections_qty[i];
//			p_object->normal[i].z /= l_connections_qty[i];
//		}
//	}
//}
//
//	//zu Initialisierung 
//char Gouraud::ObjLoad(char *p_object_name, char *p_texture_name)
//	{
//		if (Load3DS (&object,p_object_name)==0) return(0);
//		object.id_texture=LoadBMP(p_texture_name);
//		ObjCalcNormals(&object);
//		return (1);
//	}
//}
//
