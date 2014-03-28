void updatePosAndDir(){
	//ȡ��modelx��λ��
	modelx.getPosInFather(pos_modelx);
	//ȡ��modelx�ĳ���
	modelx.getDir(dir_modelx);
	//ȡ��modelx2��λ��
	modelx2.getPosInFather(pos_modelx2);
	//ȡ��modelx2�ĳ���
	modelx2.getDir(dir_modelx2);
	//ȡ��water��λ�ã�Ҫ�ر�ע�⣬water�ĸ߶Ȳ���pos_water[Y]������water.Horizon��
	water.getPosInFather(pos_water);
	//ȡ��waterBox��λ�ã�Ҫ�ر�ע�⣬waterBox�ĸ߶Ȳ���pos_waterBox[Y]������waterBox.Horizon��
	waterBox.getPosInFather(pos_waterBox);
	//ȡ��fish��λ��
	fish.getPosInFather(pos_fish);
	//ȡ��proteinλ��
	protein.getPosInFather(pos_protein);
	//������ǵ�ǰλ��
	pcell->getPosInFather(pos);
	//----------------------------superburst��posList
	//����superburst��posList
	int nsuperburst=(int)psuperburstList.size();
	posList_superburst.resize(nsuperburst);
	for(int i=0;i<nsuperburst;i++){
		psuperburstList[i]->getPosInFather(posList_superburst[i].v);
	}
	//----------------------------atomburst��posList
	//����atomburst��posList
	int natomburst=(int)patomburstList.size();
	posList_atomburst.resize(natomburst);
	for(int i=0;i<natomburst;i++){
		patomburstList[i]->getPosInFather(posList_atomburst[i].v);
	}
	//----------------------------canonball��posList
	//����canonball��posList
	int ncannonball=(int)pcell->pcannonballList.size();
	posList_cannonball.resize(ncannonball);
	for(int i=0;i<ncannonball;i++){
		pcell->pcannonballList[i]->getPosInFather(posList_cannonball[i].v);
	}
	//can
	int ncan=(int)pcanList.size();
	posList_can.resize(ncan);
	for(int i=0;i<ncan;i++){
		pcanList[i]->getPosInFather(posList_can[i].v);
	}//�õ�posList_can
	//autoCell
	int nautoCell=(int)pautoCellList.size();
	posList_autoCell.resize(nautoCell);
	dirList_autoCell.resize(nautoCell);
	for(int i=0;i<nautoCell;i++){
		pautoCellList[i]->toFather(0,0,-1,0,dirList_autoCell[i].v);
		pautoCellList[i]->getPosInFather(posList_autoCell[i].v);
		//�洢����
		pautoCellList[i]->x=posList_autoCell[i].v[X];
		pautoCellList[i]->z=posList_autoCell[i].v[Z];
	}//�õ�posList_autoCell��dirList_autoCell
	//amac
	int namac=(int)pamacList.size();
	posList_amac.resize(namac);
	for(int i=0;i<namac;i++){
		pamacList[i]->getPosInFather(posList_amac[i].v);
	}//�õ�posList_amac
	//ene
	int nene=(int)peneList.size();
	posList_ene.resize(nene);
	for(int i=0;i<nene;i++){
		peneList[i]->getPosInFather(posList_ene[i].v);
	}//�õ�posList_ene
	//gene
	int ngene=(int)pgeneList.size();
	posList_gene.resize(ngene);
	for(int i=0;i<ngene;i++){
		pgeneList[i]->getPosInFather(posList_gene[i].v);
	}//�õ�posList_gene
	//tree
	int ntree=(int)ptreeList.size();
	posList_tree.resize(ntree);
	for(int i=0;i<ntree;i++){
		ptreeList[i]->getPosInFather(posList_tree[i].v);
	}//�õ�posList_tree
	//arch
	int narch=(int)parchList.size();
	posList_arch.resize(narch);
	for(int i=0;i<narch;i++){
		posList_arch[i].v[X]=parchList[i]->x;
		posList_arch[i].v[Z]=parchList[i]->z;
		posList_arch[i].v[Y]=ground.getH(posList_arch[i].v[X],posList_arch[i].v[Z]);
		posList_arch[i].v[W]=1;
	}//�õ�posList_arch

}
void updateLODlevelAndPointOrLineSize(){//����LOD�ȼ�����߿��
	//------------------���ݾ���ѡ��ģ�Ͱ汾-------------------
	float fakeDisMax=(width_mov+height)/2;
	switch(timecounter%3){//��Ƶ
	case 0:
		//tree
		{
			int n=(int)ptreeList.size();	
			for(int i=0;i<n;i++){
				Ctree&tree=*ptreeList[i];
				if(tree.visible){
					//����tree�����ǵ�α����
					float fakeDis_3d=fabs(campos_left[X]-posList_tree[i].v[X])+fabs(campos_left[Y]-posList_tree[i].v[Y])+fabs(campos_left[Z]-posList_tree[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						tree.setIndex(0);	
					}else if(fakeDis_3d<fakeDisMax*0.833){
						tree.setIndex(1);
					}else{
						tree.setIndex(2);	
					}
				}
			}
		}
		break;
	case 1:
		//autoCell
		{
			int n=(int)pautoCellList.size();
			for(int i=0;i<n;i++){
				CautoCell&autoCell=*pautoCellList[i];
				if(autoCell.visible){
					//����autoCell�����ǵ�α����
					float fakeDis_3d=fabs(campos_left[X]-posList_autoCell[i].v[X])+fabs(campos_left[Y]-posList_autoCell[i].v[Y])+fabs(campos_left[Z]-posList_autoCell[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.38){
						autoCell.setIndex(0);
						autoCell.setCoreSlice(12);
						autoCell.setEneSlice(12);

					}else if(fakeDis_3d<fakeDisMax*0.833){
						autoCell.setIndex(1);
						autoCell.setCoreSlice(6);
						autoCell.setEneSlice(6);

					}else{
						autoCell.setIndex(2);
						autoCell.setCoreSlice(3);
						autoCell.setEneSlice(3);
					}
				}

			}
		}
		break;
	case 2:
		//cannonball
		{
			int n=(int)pcell->pcannonballList.size();
			for(int i=0;i<n;i++){
				Ccannonball&cannonball=*pcell->pcannonballList[i];
				if(cannonball.visible){
					//����cannonball�����ǵ�α����
					float fakeDis_3d=fabs(campos_left[X]-posList_cannonball[i].v[X])+fabs(campos_left[Y]-posList_cannonball[i].v[Y])+fabs(campos_left[Z]-posList_cannonball[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						cannonball.ball.setSlice(6);
					}else{
						cannonball.ball.setSlice(3);
					}

				}

			}
		}
		break;
	}//end switch
	switch(timecounter%3){//��Ƶ
	case 0:
		//amac
		{
			int n=(int)pamacList.size();
			for(int i=0;i<n;i++){
				Camac&amac=*pamacList[i];
				if(amac.visible){
					//����amac�����ǵ�α����
					float fakeDis_3d=fabs(campos_left[X]-posList_amac[i].v[X])+fabs(campos_left[Y]-posList_amac[i].v[Y])+fabs(campos_left[Z]-posList_amac[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						amac.setSlice(12,6);
					}else if(fakeDis_3d<fakeDisMax*0.666){
						amac.setSlice(6,3);
					}else{
						amac.setSlice(3,3);
					}
				}

			}
		}
		break;
	case 1:
		//ene
		{
			int n=(int)peneList.size();
			for(int i=0;i<n;i++){
				Cene&ene=*peneList[i];
				if(ene.visible){
					//����ene�����ǵ�α����
					float fakeDis_3d=fabs(campos_left[X]-posList_ene[i].v[X])+fabs(campos_left[Y]-posList_ene[i].v[Y])+fabs(campos_left[Z]-posList_ene[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						ene.setSlice(12,6);
					}else if(fakeDis_3d<fakeDisMax*0.666){
						ene.setSlice(6,3);
					}else{
						ene.setSlice(3,3);
					}
				}

			}
		}
		break;
	case 2:
		//gene
		{
			int n=(int)pgeneList.size();
			for(int i=0;i<n;i++){
				Cgene&gene=*pgeneList[i];
				if(gene.visible){
					//����gene�����ǵ�α����
					float fakeDis_3d=fabs(campos_left[X]-posList_gene[i].v[X])+fabs(campos_left[Y]-posList_gene[i].v[Y])+fabs(campos_left[Z]-posList_gene[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						gene.setSlice(12,6);
					}else if(fakeDis_3d<fakeDisMax*0.666){
						gene.setSlice(6,3);
					}else{
						gene.setSlice(3,3);
					}
				}

			}
		}
		break;
	}//end switch
	//protein
	if(protein.visible){
		//����gene�����ǵ�α����
		float fakeDis_3d=fabs(campos_left[X]-pos_protein[X])+fabs(campos_left[Y]-pos_protein[Y])+fabs(campos_left[Z]-pos_protein[Z]);
		if(fakeDis_3d<fakeDisMax*0.333){
			protein.setSlice(12,6);
		}else if(fakeDis_3d<fakeDisMax*0.666){
			protein.setSlice(6,3);
		}else{
			protein.setSlice(3,3);
		}
	}	
	//waterBox
	if(waterBox.visible){
		//����waterBox�����ǵ�α����
		float fakeDis_3d=fabs(campos_left[X]-pos_waterBox[X])+fabs(campos_left[Y]-waterBox.Horizon)+fabs(campos_left[Z]-pos_waterBox[Z]);
		if(fakeDis_3d>4300){
			waterBox.tooFar=true;
		}else{
			waterBox.tooFar=false;
		}

	}
	//water
	if(water.visible){
		//����water�����ǵ�α����
		float fakeDis_3d=fabs(pos[X]-pos_water[X])+fabs(pos[Y]-water.Horizon)+fabs(pos[Z]-pos_water[Z]);
		if(fakeDis_3d>500){
			water.tooFar=true;
		}else{
			water.tooFar=false;
		}
	}
//	cout<<water.tooFar<<endl;
	//------------superburst��LOD��pointSize
	switch(timecounter%2){//��Ƶ
	case 0:
		{
			int nsuperburst=(int)psuperburstList.size();
			for(int i=0;i<nsuperburst;i++){
				Csuperburst&superburst=*psuperburstList[i];
				if(superburst.isdied||superburst.hide||superburst.visible==false)continue;
				float superburstPos[4];
				superburst.getPosInFather(superburstPos);
				float d_2=pow2(superburstPos[X]-campos_left[X])+pow2(superburstPos[Z]-campos_left[Z]);
				float d=CarmSqrt(d_2);
				//����doLOD	
				if(d>=4000){
					superburst.LODlevel=2;
				}else if(d>=2500){
					superburst.LODlevel=1;
				}else{
					superburst.LODlevel=0;
				}
				//����superburst��pointSize
				if(d<500){
					float d1,s1,d2,s2;//��d=d1ʱsize=s1,��d=d2ʱsize=s2

					d1=500;
					s1=30;
					d2=100;
					s2=260;//150
					float a,b;//size=a*d+b�е�a,b��������
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//��Ӧ(s1-b)/d1��d1��1��Ŀ���Ƿ�ֹ���
					superburst.pointSize=min(56,a*d+b);


				}else if(d>2000){
					float d1,s1,d2,s2;//��d=d1ʱsize=s1,��d=d2ʱsize=s2

					d1=2000;
					s1=10;
					d2=5000;
					s2=6;
					float a,b;//size=a*d+b�е�a,b��������
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//��Ӧ(s1-b)/d1��d1��1��Ŀ���Ƿ�ֹ���
					superburst.pointSize=max(1,a*d+b);//Ҫ��֤����С��С��1���ܵ���Ч�������緢ɢ��
				}else{//��500<=d<=2000ʱ
					float d1,s1,d2,s2;//��d=d1ʱsize=s1,��d=d2ʱsize=s2

					d1=2000;
					s1=10;
					d2=500;
					s2=30;
					float a,b;//size=a*d+b�е�a,b��������
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//��Ӧ(s1-b)/d1��d1��1��Ŀ���Ƿ�ֹ���
					superburst.pointSize=a*d+b;
				}
			}
		}
		break;
	case 1:
		//----------------atomburst��pointSize
		{
			int natomburst=(int)patomburstList.size();
			for(int i=0;i<natomburst;i++){
				Catomburst&atomburst=*patomburstList[i];
				//����atomburst��pointSize
				float atomburstPos[4];
				atomburst.getPosInFather(atomburstPos);
				float d_2=pow2(atomburstPos[X]-campos_left[X])+pow2(atomburstPos[Z]-campos_left[Z]);
				float d=CarmSqrt(d_2);
				if(d<500){
					float d1,s1,d2,s2;//��d=d1ʱsize=s1,��d=d2ʱsize=s2

					d1=500;
					s1=16;
					d2=100;
					s2=50;
					float a,b;//size=a*d+b�е�a,b��������
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//��Ӧ(s1-b)/d1��d1��1��Ŀ���Ƿ�ֹ���
					atomburst.pointSize=a*d+b;

				}else if(d>2000){
					float d1,s1,d2,s2;//��d=d1ʱsize=s1,��d=d2ʱsize=s2

					d1=2000;
					s1=10;
					d2=5000;
					s2=6;
					float a,b;//size=a*d+b�е�a,b��������
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//��Ӧ(s1-b)/d1��d1��1��Ŀ���Ƿ�ֹ���
					atomburst.pointSize=max(1,a*d+b);//��ֹ��С��С��1���ܵ���Ч�������緢ɢ��
				}else{
					float d1,s1,d2,s2;//��d=d1ʱsize=s1,��d=d2ʱsize=s2

					d1=2000;
					s1=10;
					d2=500;
					s2=16;
					float a,b;//size=a*d+b�е�a,b��������
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//��Ӧ(s1-b)/d1��d1��1��Ŀ���Ƿ�ֹ���
					atomburst.pointSize=a*d+b;
				}
			}
		}
		break;
	}
	


}
void updateLogic(){
//	printv(pos);
	
	//----------------------------������ײ����
	//����can����ײ����
	canCgrid.clearContent();
	canCgrid.setCenter(pos[X],pos[Z]);
	canCgrid.fillContent(posList_can);
	//����autoCell��ײ����
	autoCellCgrid.clearContent();
	autoCellCgrid.setCenter(pos[X],pos[Z]);
	autoCellCgrid.fillContent(posList_autoCell);
	//����amac��ײ����
	amacCgrid.clearContent();
	amacCgrid.setCenter(pos[X],pos[Z]);
	amacCgrid.fillContent(posList_amac);
	//����ene��ײ����
	eneCgrid.clearContent();
	eneCgrid.setCenter(pos[X],pos[Z]);
	eneCgrid.fillContent(posList_ene);
	//����gene��ײ����
	geneCgrid.clearContent();
	geneCgrid.setCenter(pos[X],pos[Z]);
	geneCgrid.fillContent(posList_gene);
	//����tree��ײ����
	treeCgrid.clearContent();
	treeCgrid.setCenter(pos[X],pos[Z]);
	treeCgrid.fillContent(posList_tree);
	//����arch��ײ����
	archCgrid.clearContent();
	archCgrid.setCenter(pos[X],pos[Z]);
	archCgrid.fillContent(posList_arch);
	
	//------------------------------��ײ���(��ײ������ǰ�棬��ֹ��pListʧЧ)------------------------------------------
	//autoCell֮�����ײ��ʹ���������
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell1=*pautoCellList[i];
			if(autoCell1.visible==false)continue;
			float *pos1=posList_autoCell[i].v;
			float R1=autoCell1.Rc;
			float *dir1=dirList_autoCell[i].v;
			myvector<int> clist;//��ײ�б�
			autoCellCgrid.getclist(i,clist);
			//autoCell1��clist�е�autoCell�����ײ
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//�±��
				if(J<=i)continue;//������autoCell1�±��iС����ȵ��±��
				CautoCell&autoCell2=*pautoCellList[J];
				if(autoCell2.visible==false)continue;
				//���autoCell1��autoCell2����ײ
				float *pos2=posList_autoCell[J].v;
				float R2=autoCell2.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//auto1��auto2��ײ
					float d=R1+R2-CarmSqrt(dis2);
					//תΪ������
					float n1[4];//autoCell1�ķ�������
					float n2[4];//autoCell2�ķ�������
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
					sub((float(&)[4])(*pos2),(float(&)[4])(*pos1),n2);
					float *dir2=dirList_autoCell[J].v;
					float A1=getA(dir1,n1);
					float A2=getA(dir2,n2);
					autoCell1.rotloc010(A1);
					autoCell2.rotloc010(A2);
					autoCell1.movloc(0,0,-d/2);
					autoCell2.movloc(0,0,-d/2);
					break;//����ĳ�����󣬼�⵽����һ����ײ�����ˣ����涼��������
					
				}			
				
			}
		}
	}
		
	//*pcell��autoCell��ײ��ʹ���������
	{
		//�����ײ�б�
		CmyCell&myCell=*pcell;
		float R1=myCell.Rc;
		float *pos1=pos;//myCellλ��
		myvector<int> clist;
		autoCellCgrid.getclist(pos1[X],pos1[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];//�±��
			CautoCell&autoCell=*pautoCellList[I];	
			if(autoCell.visible==false)continue;
			//���autoCell��myCell����ײ
			float *pos2=posList_autoCell[I].v;//autoCellλ��
			float R2=autoCell.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//myCell��autoCell��ײ
				if(myCell.nomatch==false){//���myCell���Ǵ����޵�״̬
					float d=(R1+R2)-CarmSqrt(dis2);//��ײ�ķ������
					//myCell��������
					myCell.lifeplus(-1);
					//myCell����һ��
					//���������
					float n1[4];//myCell�ķ�������
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
					float back[4];//myCell�Ļ�������
					if(normalize(n1)==0)continue;
					mul(d/2,n1,back);//�õ�back
			//		//����ǰRMmat����
			//		float RMmat1[16];//myCell��RMmat����
			//		matcopy(pcell->RMmat,RMmat1);
					//myCell����
					myCell.movloc_inFather(back[X],back[Y],back[Z]);
			//		//���myCell���˺���house������ײ�������ƻ�
			//		float _pos1[4];//�ƶ���myCell��λ��
			//		pcell->toGround(0,0,0,1,_pos1);
			//		//*pcell��house��ײ���
			//		if(house.collisionTest_singlePoint(_pos1,pcell->Rc)>0){
			//			//�ָ�
			//			matcopy(RMmat1,pcell->RMmat);
			//		}
					//autoCellת��
					float n2[4]={-n1[X],-n1[Y],-n1[Z],0};//autoCell�ķ�������
					float *dir2=dirList_autoCell[I].v;
					float A2=getA(dir2,n2);
					
					autoCell.rotloc010(A2);
					//autoCellǰ��һ��
					autoCell.movloc(0,0,-d/2);
			//		//ǰ����λ�ø���
			//		float _pos2[4];
			//		autoCell.toGround(0,0,0,1,_pos2);
			//		//��autoCell����λ�ý�����house��ײ���
			//		float e_back2[4];//��������
			//		float d2=house.collisionTest_multiPoint(_pos2,autoCell.Rc,e_back2);//�������
			//		if(d2>0){
			//			//����
			//			float back2[4];
			//			mul(d2,e_back2,back2);
			//			autoCell.movloc_inFather(back2[X],back2[Y],back2[Z]);
			//			
			//		}
					
				}else{//���myCell�����޵�״̬
					//autoCell��ʧ
					autoCell.life=0;
					//autoCell������
					{
						autoCell.sourceMake(13);
						autoCell.sourcePos(pos2,k_soundDis);
						autoCell.sourcePlay();
					}
				}
				break;
				
			}
		}
	}
	
	//autoCell��tree��ײ��ʹ���������
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.visible==false)continue;
			float R1=autoCell.Rc;
			float *pos1=posList_autoCell[i].v;//autoCellλ��
			myvector<int> clist;
			//�����ײ�б�
			treeCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//�±��
				Ctree&tree=*ptreeList[J];	
				if(tree.visible==false)continue;
				//���tree��myCell����ײ
				float *pos2=posList_tree[J].v;//treeλ��
				float R2=tree.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//myCell��tree��ײ
					//����
					float backLen=R1+R2-CarmSqrt(dis2);//�Դ������Ϊ���˾���
					float back[4];//��������
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
					back[Y]=0;//����Y����
					mul(backLen/(getLen(back)+1),back,back);//��ĸ��1��Ϊ�˷�ֹ����0��
					//��back����
					autoCell.movloc_inFather(back[X],back[Y],back[Z]);
		//			//������˺�ײǽ������ǽ�ڷ��򵯻�
		//			float e_back[4];
		//			float d=house.collisionTest_singlePoint(pos1,R1,e_back);
		//			if(d>0){
		//				float back[4];
		//				mul(d,e_back,back);
		//				autoCell.movloc_inFather(back[X],back[Y],back[Z]);
		//			}
					break;
				}
			}
		}
	}
	
	//autoCell��can��ײ��ʹ���������
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.visible==false)continue;
			float R1=autoCell.Rc;
			float *pos1=posList_autoCell[i].v;//autoCellλ��
			myvector<int> clist;
			//�����ײ�б�
			canCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//�±��
				Ccan&can=*pcanList[J];	
				if(can.visible==false)continue;
				//���can��myCell����ײ
				float *pos2=posList_can[J].v;//canλ��
				float R2=can.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//myCell��can��ײ
					//����
					float backLen=R1+R2-CarmSqrt(dis2);//�Դ������Ϊ���˾���
					float back[4];//��������
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
					back[Y]=0;//����Y����
					mul(backLen/(getLen(back)+1),back,back);//��ĸ��1��Ϊ�˷�ֹ����0��
					//��back����
					autoCell.movloc_inFather(back[X],back[Y],back[Z]);
					break;
				}
			}
		}
	}
	
	
	
	//cannonball��autoCell��ײ��ʹ���������
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			float *ballpos=posList_cannonball[i].v;
			float ballR=cannonball.Rc;
			//�����ײ�б�
			myvector<int> clist;
			autoCellCgrid.getclist(ballpos[X],ballpos[Z],clist);
			//��������ײ�б���autoCell����ײ
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];
				CautoCell&autoCell=*pautoCellList[J];
				if(autoCell.visible==false)continue;
				//�ж�autoCell��cannonball�Ƿ���ײ
				float *cellpos=posList_autoCell[J].v;
				float cellR=autoCell.Rc;
				if(pow2(cellpos[X]-ballpos[X])+pow2(cellpos[Y]-ballpos[Y])+pow2(cellpos[Z]-ballpos[Z])<=pow2(cellR+ballR)){//��ײ
					//autoCell����ֵ����
					autoCell.life--;
					//autoCell������
					{
						autoCell.sourceMake(13);
						autoCell.sourcePos(cellpos,k_soundDis);
						autoCell.sourcePlay();
					}
					//cannonball��ʧ
					cannonball.disapear();
					//���ڵ���ʧ������һ����ը
					int ndiedburst=(int)pdiedburstList.size();
					if(ndiedburst!=0){//���������ը�б��л���Ԫ��
						//��pdiedburstList��ȡһ�����뵽pburstList��
						Cburst&burst=*pdiedburstList[ndiedburst-1];
						pdiedburstList.pop_back();
						burst.reSet();
						pburstList.push_back(&burst);
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}else{//���������ը�б�����û��Ԫ��
						//���������ڵ�
						pburstList.grow();
						pburstList[(int)pburstList.size()-1]=new Cburst();
						Cburst&burst=*pburstList[(int)pburstList.size()-1];
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}
					break;
				}
				
				
			}
		}
	}
	//cannonball��can��ײ��ʹ���������
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			float *ballpos=posList_cannonball[i].v;
			float ballR=cannonball.Rc;
			//�����ײ�б�
			myvector<int> clist;
			canCgrid.getclist(ballpos[X],ballpos[Z],clist);
			//��������ײ�б���can����ײ
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];
				Ccan&can=*pcanList[J];
				if(can.visible==false)continue;
				
				//�ж�can��cannonball�Ƿ���ײ
				float *canpos=posList_can[J].v;
				float canR=can.Rc;
				if(pow2(canpos[X]-ballpos[X])+pow2(canpos[Y]-ballpos[Y])+pow2(canpos[Z]-ballpos[Z])<=pow2(canR+ballR)){//��ײ
					//can������	
					{
						
						can.sourceMake(6);
						can.sourceGain(0.1);
						can.sourcePos(canpos,k_soundDis);
						can.sourcePlay();

						

					}
					if(can.life!=0){
						can.life--;	
						if(can.life==0){
							can.can.indexOfTextureID=20;
							can.dish.indexOfTextureID=17;
							//��can������һ��ԭ�ӱ�ը
							Catomburst*patomburst=NULL;
							int ndiedatomburst=(int)pdiedatomburstList.size();
							if(ndiedatomburst!=0){//�������ԭ�ӱ�ը�б��л���Ԫ��
								//��pdiedatomburstList��ȡһ�����뵽patomburstList��
								patomburst=pdiedatomburstList[ndiedatomburst-1];
								pdiedatomburstList.pop_back();
								patomburst->reSet();
								patomburstList.push_back(patomburst);
								ground.addchild(patomburst);
								patomburst->setPosInFather(canpos[X],canpos[Y]+65,canpos[Z]);
								
							}else{//���������ԭ�ӱ�ը�б�����û��Ԫ��
								//�������ɱ�ը
								patomburstList.grow();
								patomburstList[(int)patomburstList.size()-1]=new Catomburst();
								patomburst=patomburstList[(int)patomburstList.size()-1];
								ground.addchild(patomburst);
								patomburst->setPosInFather(canpos[X],canpos[Y]+65,canpos[Z]);
								patomburst->setRc(Rc_atomburst);
						//		patomburst->bshowBB=true;
							}
							//��ը����
							patomburst->sourceMake(7);
							patomburst->sourcePos(canpos[X],canpos[Y]+65,canpos[Z],k_soundDis);
							patomburst->sourcePlay();
						
						}
					}
					//can��ʧ
					cannonball.disapear();
					//���ڵ���ʧ������һ����ը
					int ndiedburst=(int)pdiedburstList.size();
					if(ndiedburst!=0){//���������ը�б��л���Ԫ��
						//��pdiedburstList��ȡһ�����뵽pburstList��
						Cburst&burst=*pdiedburstList[ndiedburst-1];
						pdiedburstList.pop_back();
						burst.reSet();
						pburstList.push_back(&burst);
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}else{//���������ը�б�����û��Ԫ��
						//���������ڵ�
						pburstList.grow();
						pburstList[(int)pburstList.size()-1]=new Cburst();
						Cburst&burst=*pburstList[(int)pburstList.size()-1];
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}
					break;
				}
				
				
			}
		}
	}
	//cannonball�������ײ
	{
		int ncannon=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannon;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			float *ballpos=posList_cannonball[i].v;
			float groundH=ground.getH(ballpos[X],ballpos[Z]);
			if(ballpos[Y]<=groundH){
				//cannonball��ʧ
				cannonball.disapear();
				//���ڵ���ʧ������һ����ը
				int ndiedburst=(int)pdiedburstList.size();
				if(ndiedburst!=0){//���������ը�б��л���Ԫ��
					//��pdiedburstList��ȡһ�����뵽pburstList��
					Cburst&burst=*pdiedburstList[ndiedburst-1];
					pdiedburstList.pop_back();
					burst.reSet();
					pburstList.push_back(&burst);
					ground.addchild(&burst);
					burst.setPosInFather(ballpos[X],groundH,ballpos[Z]);
				}else{//���������ը�б�����û��Ԫ��
					//���������ڵ�
					pburstList.grow();
					pburstList[(int)pburstList.size()-1]=new Cburst();
					Cburst&burst=*pburstList[(int)pburstList.size()-1];
					ground.addchild(&burst);
					burst.setPosInFather(ballpos[X],groundH,ballpos[Z]);
				}
			}
		}
	}
	//*pcell��can��ײ��ʹ���������
	{
		float*pos1=pos;//myCellλ��
		float R1=pcell->Rc;
		myvector<int> clist;
		canCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Ccan&can=*pcanList[I];
			if(can.visible==false)continue;
			//���can��myCell����ײ
			float *pos2=posList_can[I].v;//treeλ��
			float R2=can.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<pow2(R1+R2)){//myCell��tree��ײ
				//����
				float k=0.25;
				float backLen=((R1+R2)-CarmSqrt(dis2))*k;//��ײ�ķ�����ȵ�k��������ˣ�
				float back[4];//��������
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
				if(normalize(back)==0)continue;
				mul(backLen,back,back);
				back[Y]=0;//����Y����
				//��back����
				pcell->movloc_inFather(back[X],back[Y],back[Z]);
				break;
			}
		}
	}
	//*pcell��amac��ײ��ʹ���������
	{
		float*pos1=pos;//myCellλ��
		float R1=pcell->Rc;
		myvector<int> clist;
		amacCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Camac&amac=*pamacList[I];
			if(amac.visible==false)continue;
			//���amac��myCell����ײ
			float *pos2=posList_amac[I].v;
			float R2=amac.Rc;
			if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<=pow2(R1+R2)){//myCell��amac��ײ
				//myCell��������
				pcell->lifeplus(2);
				//���ų�С�������
				{
					alSource3f(source_eat_small,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
					alSourcePlay(source_eat_small);
				}
				//amac��ʧ
				amac.disapear();
				break;
			}
		}
	}
	//*pcell��ene��ײ
	{
		float*pos1=pos;//myCellλ��
		float R1=pcell->Rc;
		myvector<int> clist;
		eneCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Cene&ene=*peneList[I];
			if(ene.visible==false)continue;
			//���ene��myCell����ײ
			float *pos2=posList_ene[I].v;
			float R2=ene.Rc;
			if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<=pow2(R1+R2)){//myCell��ene��ײ
				//myCell��������
				pcell->eneEatplus();
				//���ų�С�������
				{
					alSource3f(source_eat_small,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
					alSourcePlay(source_eat_small);
				}
				//ene��ʧ
				ene.disapear();
				break;
				
			}
		}
	}
	//*pcell��gene��ײ
	{
		float*pos1=pos;//myCellλ��
		float R1=pcell->Rc;
		myvector<int> clist;
		geneCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Cgene&gene=*pgeneList[I];
			if(gene.visible==false)continue;
			//���gene��myCell����ײ
			float *pos2=posList_gene[I].v;
			float R2=gene.Rc;
			if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<=pow2(R1+R2)){//myCell��gene��ײ
				//����gene��effectID����myCell���Ӻ��ּ���
				if(gene.effectID==1){
					//��Ծ
					pcell->setjumpable(true);				
				}else if(gene.effectID==2){
					//�޵�
					pcell->nomatch=true;
				}else if(gene.effectID==3){
					//����
					pcell->speedup();
				}else{
					//�ӷ�
					pcell->score+=2;
				}
				//���ų�С�������
				{
					alSource3f(source_eat_small,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
					alSourcePlay(source_eat_small);
				}
				//gene��ʧ
				gene.disapear();
				break;
				
			}
		}
	}
	
	//arch�е�stick���估���桢�໥֮�����ײ���
	{
		int narch=(int)parchList.size();
		for(int k=0;k<narch;k++){
			Carch&arch=*parchList[k];
			if(arch.freeze)continue;
			//���䣨����д��ǰ����ֹ��͸���棩
			int nstick=(int)arch.pstickList.size();
			for(int i=0;i<nstick;i++){
				Cstick&stick=*arch.pstickList[i];
				stick.fall();
			}
			//stick�������ײ
			for(int i=0;i<nstick;i++){
				Cstick&stick=*arch.pstickList[i];
				myvector<Cv4>pList;
				myvector<Cv4>backList;
				myvector<float>deepList;
				stick.collisionWidthGround(pList,backList,deepList);
				//������
				float c[4];
				stick.getPc(c);	
				float Aavg[4]={0,0,0,0};
				float deepmax=0;
				int n=pList.size();
				if(n!=0){
					for(int j=0;j<n;j++){
						//----����Խ��ٶȵĹ���
						//���õ�
						float *p=pList[j].v;
						//�����ĵ����õ������r
						float r[4];
						sub((float(&)[4])(*p),c,r);	
						//��������
						float *n=backList[j].v;
						//�������
						float deep=deepList[j];
						//��λ��
						float A[4];
						cross(r,n,A);
						normalize(A);
						float lenr=getLen(r);
						float lenA; 
						if(lenr==0){
							lenA=0;
						}else{
							lenA=deep/lenr*180/pi;
						}
						mul(lenA,A,A);
						add(Aavg,A,Aavg);
						if(deep>deepmax)deepmax=deep;
					}
					
					stick.movloc_inFather(0,deepmax,0);
					mul(1.0/n,Aavg,Aavg);
					stick.rot(Aavg);
					
					
				}
				
			}
			
			//stick֮�����ײ
			for(int i=0;i<nstick;i++){
				Cstick&stick1=*arch.pstickList[i];
				bool collision=false;
				for(int j=i+1;j<=(int)arch.pstickList.size()-1;j++){
					Cstick&stick2=*arch.pstickList[j];
					//�ж�stick1��stick2����ײ��������ײ��Ӧ
					int nquad_ofstick1=(int)stick1.quadList.size();
					for(int u=0;u<nquad_ofstick1;u++){
						Cobj&quad1=stick1.quadList[u];
						//��quad1����������
						float pos1[4];
						quad1.toModel(0,0,0,1,pos1);//��ת��ģ�Ϳռ�
						stick1.toFather(pos1[X],pos1[Y],pos1[Z],pos1[W],pos1);//��ת������ռ�
						int nquad_ofstick2=(int)stick2.quadList.size();
						for(int v=0;v<nquad_ofstick2;v++){
							Cobj&quad2=stick2.quadList[v];
							//��quad2����������
							float pos2[4];
							quad2.toModel(0,0,0,1,pos2);//��ת��ģ�Ϳռ�
							stick2.toFather(pos2[X],pos2[Y],pos2[Z],pos2[W],pos2);//��ת������ռ�
							//�ж�quad1��quad2�Ƿ���ײ
							float len_2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
							if(len_2<=pow2(stick1.d/2+stick2.d/2)){//��ײ
								collision=true;
								//����ײ��
								float p[4];
								add(pos1,pos2,p);
								mul(0.5,p,p);
								//������
								float c1[4];
								float c2[4];
								stick1.getPc(c1);
								stick2.getPc(c2);
								//��ʸ��
								float r1[4];
								float r2[4];
								sub(p,c1,r1);
								sub(p,c2,r2);
								//�󷴵�����
								float n1[4];
								float n2[4];
								sub(pos1,pos2,n1);
								normalize(n1);
								sub(pos2,pos1,n2);
								normalize(n2);
								//�����
								float len=CarmSqrt(len_2);
								float deep1=stick1.d/2+stick2.d/2-len;
								float deep2=stick1.d/2+stick2.d/2-len;
								//����p��back��deep����stick1��stick2
								//stick1ת��
								//��λ��
								float A1[4];
								cross(r1,n1,A1);
								normalize(A1);
								float lenr1=getLen(r1);
								float lenA1; 
								if(lenr1==0){
									lenA1=0;
								}else{
									lenA1=deep1/lenr1*180/pi;
								}
								mul(0.2*lenA1,A1,A1);
								stick1.rot(A1);
								//��λ��
								float back1[4];
								mul(deep1,n1,back1);
								stick1.movloc_inFather(back1[X],back1[Y],back1[Z]);
								if(back1[Y]>0){
									mul(0.8,stick1.vc,stick1.vc);
									float vc1len=getLen(stick1.vc);
									if(vc1len<3){
										mul(1.0/vc1len,stick1.vc,stick1.vc);
									}
								}
								//stick2ת��
								//��λ��
								float A2[4];
								cross(r2,n2,A2);
								normalize(A2);
								float lenr2=getLen(r2);
								float lenA2; 
								if(lenr2==0){
									lenA2=0;
								}else{
									lenA2=deep2/lenr2*180/pi;
								}
								mul(0.2*lenA2,A2,A2);
								stick2.rot(A2);
								//��λ��
								float back2[4];
								mul(deep2,n2,back2);
								stick2.movloc_inFather(back2[X],back2[Y],back2[Z]);
								if(back2[Y]>0){
									mul(0.8,stick2.vc,stick2.vc);
									float vc2len=getLen(stick2.vc);
									if(vc2len<3){
										mul(1.0/vc2len,stick2.vc,stick2.vc);
									}
								}
							}
						}
					}
					
				}
				if(collision)
				{	
					float c[4];
					stick1.getPc(c);
					float groundHorizon=ground.getH(c[X],c[Z]);
					if(c[Y]-stick1.d/2<=groundHorizon){
						stick1.movloc_inFather(0,fabs(c[Y]-stick1.d/2-groundHorizon),0);
						stick1.freeze=true;//һ�������ŵأ��Ͷ��ᣬ������ֹ�Ժ��ٲ�������Ȼ��ֻ�еײ�Ĳ��ܶ��ᣬ����������ȶ������㹻
					}
				}
			}
			if(showShadow){
				arch.mesh2mesh_world();
				arch.remakeBondEdgeList(light_pos);
				arch.remakeSV(light_pos);
			}
		}
			
	}
	
		//arch��������ײ��ʹ���������
	{
		CmyCell&myCell=*pcell;
		float pos1[4];
		myCell.getPosInFather(pos1);
		float R1=myCell.Rc;
		myvector<int> clist;
		archCgrid.getclist(pos1[X],pos1[Z],clist);
		int nc=(int)clist.size();
		for(int k=0;k<nc;k++){
			int K=clist[k];//�±��
			Carch&arch=*parchList[K];
			if(arch.visible==false)continue;
			//���myCell��arch�Ƿ���ײ
			float pos_arch[4];
			veccopy(posList_arch[K].v,pos_arch);
			float R_arch=Rc_arch;
			bool mycell_arch_collision=false;
			if(pow2(pos1[X]-pos_arch[X])+pow2(pos1[Y]-pos_arch[Y])+pow2(pos1[Z]-pos_arch[Z])<=pow2(R1+R_arch)){//��ײ
				mycell_arch_collision=true;
			}//�õ�mycell_arch_collision
			if(!mycell_arch_collision)continue;//�������ײ��������ϸ��⣬����
			int nstick=(int)arch.pstickList.size();
			for(int i=0;i<nstick;i++){
				Cstick&stick=*arch.pstickList[i];
				//���stick��myCell��ײ
				//�����ľ���ƽ��
				float pos2[4];
				stick.getPosInFather(pos2);
				float R2=stick.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2>pow2(R1+R2)){//һ������ײ
					continue;
				}
				//��stick�����߶�
				float head[4];
				stick.toFather(0,stick.len()/2,0,1,head);
				float bottom[4];
				stick.toFather(0,-stick.len()/2,0,1,bottom);
				float hmax=max(head[Y],bottom[Y]);
				if(hmax<pos[Y]){//һ������ײ
					continue;
				}
				//����˵������hmax>=pos[Y]��dis2<=pow2(R1+R2)��������ײ	
				//������ײ��Ӧ
				float k=0.2;
				float d=((R1+R2)-CarmSqrt(dis2))*k;//��ײ�ķ�����ȵ�k��������ˣ�
				//myCell����
				//���������
				float n1[4];//myCell�ķ�������
				sub(pos1,pos2,n1);
				float back[4];
				normalize(n1);
				mul(d,n1,back);
				back[Y]=0;//����Y����
		//		//����ǰRMmat����
		//		float RMmat1[16];//myCell��RMmat����
		//		matcopy(pcell->RMmat,RMmat1);	
				//����
				myCell.movloc_inFather(back[X],back[Y],back[Z]);
		//		//���myCell���˺���house������ײ�������ƻ�
		//		float _pos1[4];//�ƶ���myCell��λ��
		//		pcell->toGround(0,0,0,1,_pos1);
		//		//myCell��house��ײ���
		//		if(house.collisionTest_singlePoint(_pos1,pcell->Rc)>0){//��ײ
		//			//�ָ�
		//			matcopy(RMmat1,pcell->RMmat);
		//		}else{//δ��ײ
		//			//����myCellλ�÷������ƶ������Ը���pos1����������Ϊ�˸���ȷ����ֹ�𶯣��������򵥵�����¾�δ��������
		//			veccopy(_pos1,pos1);
		//		}

			}
		}
	}

	//arch��autoCell��ײ,ʹ���������
	{
		int nautoCell=(int)pautoCellList.size();
		for(int u=0;u<nautoCell;u++){
			CautoCell&autoCell=*pautoCellList[u];
			if(autoCell.visible==false)continue;
			float pos1[4];
			autoCell.getPosInFather(pos1);
			float R1=autoCell.Rc;
			myvector<int> clist;
			archCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int k=0;k<nc;k++){
				int K=clist[k];//�±��
				Carch&arch=*parchList[K];
				if(arch.visible==false)continue;
				//���autoCell��arch�Ƿ���ײ
				float pos_arch[4];
				veccopy(posList_arch[K].v,pos_arch);
				float R_arch=Rc_arch;
				bool autocell_arch_collision=false;
				if(pow2(pos1[X]-pos_arch[X])+pow2(pos1[Y]-pos_arch[Y])+pow2(pos1[Z]-pos_arch[Z])<=pow2(R1+R_arch)){//��ײ
					autocell_arch_collision=true;
				}//�õ�autocell_arch_collision
				if(!autocell_arch_collision)continue;//�������ײ��������ϸ��⣬����
				int nstick=(int)arch.pstickList.size();
				for(int i=0;i<nstick;i++){
					Cstick&stick=*arch.pstickList[i];
					//���stick��autoCell��ײ
					//�����ľ���ƽ��
					float pos2[4];
					stick.getPosInFather(pos2);
					float R2=stick.Rc;
					float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
					if(dis2>pow2(R1+R2)){//һ������ײ
						continue;
					}
					//��stick�����߶�
					float head[4];
					stick.toFather(0,stick.len()/2,0,1,head);
					float bottom[4];
					stick.toFather(0,-stick.len()/2,0,1,bottom);
					float hmax=max(head[Y],bottom[Y]);
					if(hmax<pos[Y]){//һ������ײ
						continue;
					}
					//����˵������hmax>=pos[Y]��dis2<=pow2(R1+R2)��������ײ	
					//������ײ��Ӧ
					float d=(R1+R2)-CarmSqrt(dis2);//��ײ�ķ������
					//autoCell����
					float n1[4];//myCell�ķ�������
					sub(pos1,pos2,n1);
					//autoCell����һ��
					float back[4];
					normalize(n1);
					mul(d,n1,back);
					back[Y]=0;
					autoCell.movloc_inFather(back[X],back[Y],back[Z]);
					break;
					
				}
			}
		}
	}
	//cannonball��arch��ײ��ʹ���������
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			//��ǰ�ڵ�λ��
			float *ballpos=posList_cannonball[i].v;
			//�ڵ��뾶
			float ballR=cannonball.Rc;
			myvector<int> clist;
			archCgrid.getclist(ballpos[X],ballpos[Z],clist);
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//�±��
				Carch&arch=*parchList[J];
				if(arch.visible==false)continue;
				//���cannonball��arch�Ƿ���ײ
				//�ȿ��Ƿ���а�Χ��
				float pos_arch[4];
				veccopy(posList_arch[J].v,pos_arch);
				float R_arch=Rc_arch;
				bool autocell_arch_collision=false;
				if(pow2(ballpos[X]-pos_arch[X])+pow2(ballpos[Y]-pos_arch[Y])+pow2(ballpos[Z]-pos_arch[Z])<=pow2(ballR+R_arch)){//��ײ
					autocell_arch_collision=true;
				}//�õ�autocell_arch_collision
				if(!autocell_arch_collision)continue;//��������а�Χ�򣬲�����ϸ��⣬����
				//�ٿ��߶��Ƿ����
				//��arch������stick�����ߵ�
				float Hmax=-inf;
				int nstick=(int)arch.pstickList.size();
				for(int u=0;u<nstick;u++){
					Cstick&stick=*arch.pstickList[u];
					//��stick�����ߵ�
					float head[4];
					stick.toFather(0,stick.len()/2,0,1,head);
					float bottom[4];
					stick.toFather(0,-stick.len()/2,0,1,bottom);
					float hmax=max(head[Y],bottom[Y]);
					if(hmax>Hmax)Hmax=hmax;
				}//�õ�Hmax
				if(Hmax<ballpos[Y])continue;//����߶Ȳ����ʣ�����
				//����һ�����
				for(int k=0;k<nstick;k++){
					Cstick&stick=*arch.pstickList[k];
					//���cannonball��stick�İ�Χ�����ײ
					float stickballpos[4];
					stick.getPosInFather(stickballpos);
					float stickballR=stick.Rc;
					if(pow2(stickballpos[X]-ballpos[X])+pow2(stickballpos[Y]-ballpos[Y])+pow2(stickballpos[Z]-ballpos[Z])<=pow2(stickballR+ballR)){//��ײ
						if(arch.freeze){
							arch.life--;
							if(arch.life==0){
								arch.setfreeze(false);
								//���ŵ�������
								arch.sourceMake(8);
								arch.sourcePos(pos_arch,k_soundDis);
								arch.sourcePlay();
								//���Ǽӷ�
								pcell->score+=15;
							}
						}
						//cannonball��ʧ
						cannonball.disapear();
						//���ڵ���ʧ������һ����ը
						Cburst*pburst=NULL;
						int ndiedburst=(int)pdiedburstList.size();
						if(ndiedburst!=0){//���������ը�б��л���Ԫ��
							//��pdiedburstList��ȡһ�����뵽pburstList��
							pburst=pdiedburstList[ndiedburst-1];
							pdiedburstList.pop_back();
							pburst->reSet();
							pburstList.push_back(pburst);
							ground.addchild(pburst);
							pburst->setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
						}else{//���������ը�б�����û��Ԫ��
							//�������ɱ�ը
							pburstList.grow();
							pburstList[(int)pburstList.size()-1]=new Cburst();
							pburst=pburstList[(int)pburstList.size()-1];
							ground.addchild(pburst);
							pburst->setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
						}
						//Ϊpburst��������
						{
							pburst->sourceMake(9);
							pburst->sourcePos(ballpos,k_soundDis);
							pburst->sourcePlay();
						}
						break;
						
					}
					
					
				}
			}
		}
	}
	//cannonball��house��ײ
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			//��ǰ�ڵ�λ��
			float *ballpos=posList_cannonball[i].v;
			//ǰһʱ���ڵ�λ��
			float ballposf[4];
			cannonball.toFather(0,0,300/2,1,ballposf);
			//�ж��߶�ballposf--ballpos�Ƿ���house�ཻ
			float p[4];//��������
			if(house.collisionTest_lineSeg(ballposf,ballpos,p)){
				//cannonball��ʧ
				cannonball.disapear();
				//���ڵ���ʧ������һ����ը
				Cburst*pburst=NULL;
				int ndiedburst=(int)pdiedburstList.size();
				if(ndiedburst!=0){//���������ը�б��л���Ԫ��
					//��pdiedburstList��ȡһ�����뵽pburstList��
					pburst=pdiedburstList[ndiedburst-1];
					pdiedburstList.pop_back();
					pburst->reSet();
					pburstList.push_back(pburst);
					ground.addchild(pburst);
					pburst->setPosInFather(p[X],p[Y],p[Z]);
				}else{//���������ը�б�����û��Ԫ��
					//���������ڵ�
					pburstList.grow();
					pburstList[(int)pburstList.size()-1]=new Cburst();
					pburst=pburstList[(int)pburstList.size()-1];
					ground.addchild(pburst);
					pburst->setPosInFather(p[X],p[Y],p[Z]);
				}
				//pburst��Ч������ǽ���ϵ�����
				pburst->sourceMake(9);
				pburst->sourcePos(p,k_soundDis);
				pburst->sourcePlay();
			}
		}
	}
	
	//�����ڵ��Ƿ񼺴ﵽ���
	{
		int ncanonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncanonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			//�������pcell��Զ������ʧ
			float *cannonballpos=posList_cannonball[i].v;
			float vec[4];
			sub(pos,(float(&)[4])(*cannonballpos),vec);
			if(getLen_2(vec)>=2000*2000){
				cannonball.disapear();
			}
		}
	}
	//modelx��pcell��ײ
	{
		if(modelx.visible){
			float *pos1=pos;
			float *pos2=pos_modelx;
			float R1=pcell->Rc;
			float R2=modelx.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//��ײ
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//��ײ�ķ������
				                                     //����fabs��Ϊ�˱���dΪ��ֵ��֮���Ի����dΪ��ֵ�����������ΪCarmSqrt����ȷ
				//pcell����һ��
				//���������
				float n1[4];//pcell�ķ�������
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
				n1[Y]=0;
				float back[4];//pcell�Ļ�������
				if(normalize(n1)!=0){
					mul(d/2,n1,back);//�õ�back
					//pcell����
					pcell->movloc_inFather(back[X],back[Y],back[Z]);
					//modelx����
					//����ǰ�������
					float RMmatf[16];
					matcopy(modelx.RMmat,RMmatf);
					//����
					modelx.movloc_inFather(-back[X],-back[Y],-back[Z]);
					//���modelx��house����ײ
					float _pos_modelx[4];
					modelx.getPosInFather(_pos_modelx);
					float e_back[4];
					float d=house.collisionTest_multiPoint_pcell(_pos_modelx,modelx.Rc,e_back);//������multiPoint��������ܻᴩǽ
					//ԭ�������singlePoint�л��������ļ��㲻׼ȷ�Ӷ����´���Ļ��˷����й�
					if(d>0){
						//�ָ�
						matcopy(RMmatf,modelx.RMmat);
					}
					//����
					bool allstopped;//�Ƿ�����������ֹͣ��
					ALint state1;
					alGetSourcei(source_modelx_hellow_i_m_beavis, AL_SOURCE_STATE,&state1);
					ALint state2;
					alGetSourcei(source_modelx_what_are_you_doing, AL_SOURCE_STATE,&state2);
					if((state1==AL_STOPPED||state1==AL_INITIAL)&&(state2==AL_STOPPED||state2==AL_INITIAL)){
						allstopped=true;
					}else{
						allstopped=false;
					}
					if(allstopped){
						//����modelx��pcell�ĳ�����������ĸ�����
						float dir_modelx[4];
						modelx.getDir(dir_modelx);
						if(dot(n1,dir_modelx)>=0){//ӭ������
							//����hellow, i'm beavis
							alSource3f(source_modelx_hellow_i_m_beavis,AL_POSITION,pos_modelx[X]*k_soundDis,pos_modelx[Y]*k_soundDis,pos_modelx[Z]*k_soundDis);
							alSourcePlay(source_modelx_hellow_i_m_beavis);
						}else{//׷β
							//����what are you doing
							alSource3f(source_modelx_what_are_you_doing,AL_POSITION,pos_modelx[X]*k_soundDis,pos_modelx[Y]*k_soundDis,pos_modelx[Z]*k_soundDis);
							alSourcePlay(source_modelx_what_are_you_doing);
						}	
					}	
				}
			}
		}	
	}
	//modelx��modelx2��ײ
	{
		if(modelx.visible){
			float *pos1=pos_modelx;
			float *pos2=pos_modelx2;
			float R1=modelx.Rc;
			float R2=modelx2.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//��ײ
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//��ײ�ķ������
				                                     //����fabs��Ϊ�˱���dΪ��ֵ��֮���Ի����dΪ��ֵ�����������ΪCarmSqrt����ȷ
				float n1[4];//modelx�ķ�������
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
				n1[Y]=0;
				float back[4];//modelx�Ļ�������
				if(normalize(n1)!=0){
					mul(d,n1,back);//�õ�back
					//modelx����
					modelx.movloc_inFather(back[X],back[Y],back[Z]);
				}
			}
		}	
	}
	//modelx2��pcell��ײ
	{
		if(modelx2.visible){
			float *pos1=pos;
			float *pos2=pos_modelx2;
			float R1=pcell->Rc;
			float R2=modelx2.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//��ײ
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//��ײ�ķ������
				                                     //����fabs��Ϊ�˱���dΪ��ֵ��֮���Ի����dΪ��ֵ�����������ΪCarmSqrt����ȷ
				//pcell����һ��
				//���������
				float n1[4];//pcell�ķ�������
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
				n1[Y]=0;
				float back[4];//pcell�Ļ�������
				if(normalize(n1)!=0){
					mul(d,n1,back);//�õ�back
					//pcell����
					pcell->movloc_inFather(back[X],back[Y],back[Z]);
				}
			}
		}	
	}
	//modelx��arch��ײ��ʹ���������
	{
		if(modelx.visible){
			float *pos1=pos_modelx;
			float R1=modelx.Rc;
			myvector<int> clist;
			archCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int k=0;k<nc;k++){
				int K=clist[k];//�±��
				Carch&arch=*parchList[K];
				if(arch.visible==false)continue;
				//���modelx��arch�Ƿ���ײ
				float pos_arch[4];
				veccopy(posList_arch[K].v,pos_arch);
				float R_arch=Rc_arch/2;
				float dis2=pow2(pos1[X]-pos_arch[X])+pow2(pos1[Y]-pos_arch[Y])+pow2(pos1[Z]-pos_arch[Z]);
				if(dis2<=pow2(R1+R_arch)){//��ײ
					//������ײ��Ӧ
					float k=0.2;
					float d=((R1+R_arch)-CarmSqrt(dis2))*k;//��ײ�ķ�����ȵ�k��������ˣ�
					//modelx����
					//���������
					float n1[4];//modelx�ķ�������
					sub((float(&)[4])(*pos1),pos_arch,n1);
					float back[4];
					normalize(n1);
					mul(d,n1,back);
					back[Y]=0;//����Y����
					//����
					modelx.movloc_inFather(back[X],back[Y],back[Z]);
				
					
				}
			}
		}
	}
	//modelx��autoCell��ײ��ʹ���������
	{
		if(modelx.visible){
			//�����ײ�б�
			float R1=modelx.Rc;
			float *pos1=pos_modelx;
			myvector<int> clist;
			autoCellCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int i=0;i<nc;i++){
				int I=clist[i];//�±��
				CautoCell&autoCell=*pautoCellList[I];	
				if(autoCell.visible==false)continue;
				//���autoCell��modelx����ײ
				float *pos2=posList_autoCell[I].v;//autoCellλ��
				float R2=autoCell.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//modelx��autoCell��ײ
					float d=fabs((R1+R2)-CarmSqrt(dis2));//��ײ�ķ������
					//modelx����һ��
					//���������
					float n1[4];//modelx�ķ�������
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
					n1[Y]=0;
					float back[4];//modelx�Ļ�������
					if(normalize(n1)==0)continue;
					mul(d/2,n1,back);//�õ�back
					//modelx����
					modelx.movloc_inFather(back[X],back[Y],back[Z]);
					//autoCellת��
					float n2[4]={-n1[X],-n1[Y],-n1[Z],0};//autoCell�ķ�������
					float *dir2=dirList_autoCell[I].v;
					float A2=getA(dir2,n2);
					autoCell.rotloc010(A2);
					//autoCellǰ��һ��
					autoCell.movloc(0,0,-d/2);
					
					break;
					
				}
			}
		}
	}
	//modelx2��autoCell��ײ��ʹ���������
	{
		if(modelx2.visible){
			//�����ײ�б�
			float R1=modelx2.Rc;
			float *pos1=pos_modelx2;
			myvector<int> clist;
			autoCellCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int i=0;i<nc;i++){
				int I=clist[i];//�±��
				CautoCell&autoCell=*pautoCellList[I];	
				if(autoCell.visible==false)continue;
				//���autoCell��modelx����ײ
				float *pos2=posList_autoCell[I].v;//autoCellλ��
				float R2=autoCell.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//modelx��autoCell��ײ
					float d=fabs((R1+R2)-CarmSqrt(dis2));//��ײ�ķ������
					//���������
					float n2[4];//autoCell�ķ�������
					sub((float(&)[4])(*pos2),(float(&)[4])(*pos1),n2);
					n2[Y]=0;
					//autoCellת��
					float *dir2=dirList_autoCell[I].v;
					float A2=getA(dir2,n2);
					autoCell.rotloc010(A2);
					//autoCellǰ��һ��
					autoCell.movloc(0,0,-d);
					
					break;
					
				}
			}
		}
	}
	
	
	//metalBall��pcell��ײ
	{
		if(metalBall.visible){
			float *pos1=pos;
			float pos2[4];
			metalBall.getPosInFather(pos2);
			float R1=pcell->Rc;
			float R2=metalBall.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//��ײ
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//��ײ�ķ������
				                                     //����fabs��Ϊ�˱���dΪ��ֵ��֮���Ի����dΪ��ֵ�����������ΪCarmSqrt����ȷ
				//pcell����һ��
				//���������
				float n1[4];//pcell�ķ�������
				sub((float(&)[4])(*pos1),pos2,n1);
				n1[Y]=0;
				float back[4];//pcell�Ļ�������
				if(normalize(n1)!=0){
					mul(d,n1,back);//�õ�back
					//pcell����
					pcell->movloc_inFather(back[X],back[Y],back[Z]);
				}
			}
		}	
	}
	//--------------------���can����arch��modelx2������������ƶ�����������㹻Զ
	//���can��modelx2���������ƶ�can
	{
		int nCan=(int)pcanList.size();
		for(int i=0;i<nCan;i++){
			Ccan&can=*pcanList[i];
			float canX=posList_can[i].v[X];
			float canZ=posList_can[i].v[Z];
			float m2X=pos_modelx2[X];
			float m2Z=pos_modelx2[Z];
			float d=CarmSqrt(pow2(canX-m2X)+pow2(canZ-m2Z));
			if(d<=modelx2.Rc+Rc_can){
				//��can�����ƶ�
				//���������
				float back[4]={canX-m2X,0,canZ-m2Z,0};
				normalize(back);
				mul(d,back,back);
				//��can���л���
				can.movloc_inFather(back[X],back[Y],back[Z]);
			}
			
		}
	}
	//���arch��modelx2���������ƶ�arch
	{
		int nArch=(int)parchList.size();
		for(int i=0;i<nArch;i++){
			Carch&arch=*parchList[i];
			float archX=posList_arch[i].v[X];
			float archZ=posList_arch[i].v[Z];
			float m2X=pos_modelx2[X];
			float m2Z=pos_modelx2[Z];
			float d=CarmSqrt(pow2(archX-m2X)+pow2(archZ-m2Z));
			if(d<=modelx2.Rc+Rc_arch){
				//��carch�����ƶ�
				//���������
				float back[4]={archX-m2X,0,archZ-m2Z,0};
				normalize(back);
				mul(d,back,back);
				//��can���л���
				arch.movloc_inFather(back[X],back[Y],back[Z]);
				arch.storexz(arch.x+back[X],arch.z+back[Z]);//**
			}
			
		}
	}
	//--------------------�ƶ�----------------------------------
	//modelx�˶�
	{
		//�����ܿɲ��ɼ�����Ҫ�ƶ��������䵽������
		if(modelx.visible){
			modelx.autoMov(house);
		}else{
			modelx.autoMov_whenVisibleIsFalse();
		}
		modelx.downToGround_soft();
		//���ܿɼ���񣬶��ǽ��ж����������������н�����Ҫ�κο�����ֻ��ʱ��++����
		modelx.animationAdvance_rollback(40);
		
	//	cout<<"modelx.visible:"<<modelx.visible<<endl;
	//	cout<<"modelx.visible_reflect:"<<modelx.visible_reflect<<endl;

	}
	//modelx2
	{
	//	modelx2.downToGround_soft();
		//���ܿɼ���񶼲����������������������κο���������ʱ��++����
		modelx2.animationAdvance_rollback(40);
			
		
		//��pcell��modelx2�ľ���ƽ��
		float d2=pow2(pos[X]-pos_modelx2[X])+pow2(pos[Y]-pos_modelx2[Y])+pow2(pos[Z]-pos_modelx2[Z]);
		const float peakValue=6;
		const float maxDis=2000;
		const float k=-peakValue/maxDis;
		float d=fabs(CarmSqrt(d2));
		float currentValue=max(0,peakValue+k*d);
		alSourcef(source_music, AL_GAIN,currentValue);
		if(currentValue>0){//����
			ALint state;
			alGetSourcei(source_music, AL_SOURCE_STATE,&state);
			switch(state){//AL_SOURCE_STATEֻ��������
			case AL_INITIAL:
			case AL_PAUSED:
			case AL_STOPPED:
				alSourcePlay(source_music);
				break;
			case AL_PLAYING:
				break;
			}
			//������Դ����
			alSource3f(source_music,AL_POSITION,pos_modelx2[X]*k_soundDis,pos_modelx2[Y]*k_soundDis,pos_modelx2[Z]*k_soundDis);
		}else{//����
			alSourcePause(source_music);
		}
		
	}
	//fish�ζ�
	if(fish.visible){
		fish.shakeBody(5);
		fish.updateSkin();
	}	
	//�����Ƿ�ɼ�����Ҫ�ƶ�
	fish.autoMov(house);
	//����fish��Դ����
	{
		//��pcell��fish�ľ���ƽ��
		float d2=pow2(pos[X]-pos_fish[X])+pow2(pos[Y]-pos_fish[Y])+pow2(pos[Z]-pos_fish[Z]);
		const float peakValue=3.5;
		const float maxDis=3200;
		const float k=-peakValue/maxDis;
		float d=fabs(CarmSqrt(d2));
		float currentValue=max(0,peakValue+k*d);
		alSourcef(source_fish_move_on_water, AL_GAIN,currentValue);
		if(currentValue>0){//����
			ALint state;
			alGetSourcei(source_fish_move_on_water, AL_SOURCE_STATE,&state);
			switch(state){//AL_SOURCE_STATEֻ��������
			case AL_INITIAL:
			case AL_PAUSED:
			case AL_STOPPED:
				alSourcePlay(source_fish_move_on_water);
				break;
			case AL_PLAYING:
				break;
			}
			//������Դ����
			alSource3f(source_fish_move_on_water,AL_POSITION,pos_fish[X]*k_soundDis,pos_fish[Y]*k_soundDis,pos_fish[Z]*k_soundDis);
		}else{//����
			alSourcePause(source_fish_move_on_water);
		}
	}


	//ԭ�ӱ�ը
	{
		int natomburst=(int)patomburstList.size();
		for(int i=0;i<natomburst;i++){
			Catomburst&atomburst=*patomburstList[i];
			atomburst.burst();
			//����atomburst�ĸ�compball��ɫ
			{
				atomburst.updateColorOfcompballs();
			}
		}

	}
	//��������
	{
		int nbigcannon=(int)pbigcannonList.size();
		for(int i=0;i<nbigcannon;i++){
			Cbigcannon&bigcannon=*pbigcannonList[i];
			if(bigcannon.visible){
				bigcannon.vy+=5;
				float bigcannonposf[4];
				bigcannon.getPosInFather(bigcannonposf);
				bigcannon.movloc(0,-bigcannon.vy,-200);
				bigcannon.burst();
			
				float bigcannonpos[4];
				bigcannon.getPosInFather(bigcannonpos);
				bigcannon.sourcePos(bigcannonpos,k_soundDis);//������Դλ��
				float waterH=water.Horizon;
				float groundH=ground.getH(bigcannonpos[X],bigcannonpos[Z]);
				if(groundH==inf){//����������̫Զ������Զ���ĵ��滹û���ɣ���ʱ����inf��Ҫ�����жϣ���Ϊ-inf���Ա����ȡmaxʱ�����Ե�
					groundH=-inf;
				}
				float H=max(waterH,groundH);
				if(bigcannonpos[Y]<H){//�������ײ
					//��bigcannon����Ϊ���ɼ�
					bigcannon.visible=false;
					//ֹͣ��������
					ALint state=bigcannon.sourceState();
					if(state==AL_PLAYING||state==AL_PAUSED){
						bigcannon.sourceStop();
					}
					//����һ��superburst
					//����superburst
					Csuperburst*psuperburst=NULL;
					//�����ըλ����campos_left̫�������������ͱ�ը����������������α�ը��Ģ���ͱ�ը
					int type;
					float d2=pow2(bigcannonpos[X]-campos_left[X])+pow2(bigcannonpos[Z]-campos_left[Z]);
					if(d2<=2000*2000){
						type=1;
					}else{
						type=rand()%2;
					}
				
					if(type==0){
						//��psuperburstList_mushroom��ȡһ��isdied��
						for(int j=0;j<nsuperburstMax;j++){
							Csuperburst&superburst=*psuperburstList_mushroom[j];
							if(superburst.isdied){
								psuperburst=&superburst;
								break;
							}
						}//�õ�psuperburst
					
					}else{//type==1
						//��psuperburstList_ball��ȡһ��isdied��
						for(int j=0;j<nsuperburstMax;j++){
							Csuperburst&superburst=*psuperburstList_ball[j];
							if(superburst.isdied){
								psuperburst=&superburst;
								break;
							}
						}//�õ�psuperburst

					}
					if(psuperburst==NULL){
					//	cout<<"error: psuperburst==NULL"<<endl;
					
					}else{//psuerburst!=NULL
						psuperburst->reSet();
						//����superburst
						psuperburst->setPosInFather(bigcannonpos[X],H-45,bigcannonpos[Z]);
						//��psuperburst���뵽������
						ground.addchild(psuperburst);
						//��psuperburst���뵽psuperburstList
						psuperburstList.push_back(psuperburst);
						//��psuperburst��������
						psuperburst->sourceMake(3);
						psuperburst->sourcePos(bigcannonpos[X],H-45,bigcannonpos[Z],k_soundDis);
						psuperburst->sourcePlay();
					}

					
				}else{//���������ײ
					int type;
					bool collision=false;
					//����Ƿ����컨����ײ��ذ���ײ
					float houseCeilH=house.getH_ceil(bigcannonposf);//ǰһʱ������bsp�ڵ���컨��߶�
					if(bigcannonpos[Y]>=houseCeilH){//���컨����ײ
						type=rand()%2;
						collision=true;
					}else{//�����컨����ײ
						//����Ƿ���صذ���ײ
						float houseFloorH=house.getH_floor(bigcannonposf);//ǰһʱ������bsp�ڵ�ĵذ�߶�
						if(bigcannonpos[Y]<=houseFloorH){//��ذ���ײ
							type=rand()%2;
							collision=true;
						}else{//����ذ���ײ
							//����Ƿ���ǽ����ײ
							float e_back[4];
							if(house.collisionTest_singlePoint(bigcannonpos,Rc_bigcannon,e_back)!=-1){
								type=1;
								collision=true;	
							}
						}
					}
					//����collision������Ӧ
					if(collision){		
						//��bigcannon����Ϊ���ɼ�
						bigcannon.visible=false;
						//����ֹͣ
						bigcannon.sourceStop();
						//����һ��superburst
						//����superburst
						Csuperburst*psuperburst=NULL;
						if(type==0){
							//��psuperburstList_mushroom��ȡһ��isdied��
							for(int j=0;j<nsuperburstMax;j++){
								Csuperburst&superburst=*psuperburstList_mushroom[j];
								if(superburst.isdied){
									psuperburst=&superburst;
									break;
								}
							}//�õ�psuperburst
							
						}else{//type==1
							//��psuperburstList_ball��ȡһ��isdied��
							for(int j=0;j<nsuperburstMax;j++){
								Csuperburst&superburst=*psuperburstList_ball[j];
								if(superburst.isdied){
									psuperburst=&superburst;
									break;
								}
							}//�õ�psuperburst
							
						}
						if(psuperburst==NULL){
						//	cout<<"error: psuperburst==NULL"<<endl;
							
						}else{//psuerburst!=NULL
							psuperburst->reSet();
							//����superburst
							float H;
							if(type==0){
								H=bigcannonpos[Y]-13;
							}else{
								H=bigcannonpos[Y];
							}
							psuperburst->setPosInFather(bigcannonpos[X],H,bigcannonpos[Z]);
							//��psuperburst���뵽������
							ground.addchild(psuperburst);
							//��psuperburst���뵽psuperburstList
							psuperburstList.push_back(psuperburst);
							//��psuperburst��������
							psuperburst->sourceMake(3);
							float pos[4]={bigcannonpos[X],H,bigcannonpos[Z],1};
							psuperburst->sourcePos(pos,k_soundDis);
							psuperburst->sourcePlay();
						}
						
					}
					
				}
				
				
			}
		}
	}

	//���ƴ�ԭ�ӱ�ը����
	{
		const int nsuperburst=(int)psuperburstList.size();
		if(nsuperburst>nsuperburstMax*0.6){
			//��psuperburstList[0]����Ϊdied
			psuperburstList[0]->setDied(true);
		}
	}
	//***��ԭ�ӱ�ը
	{

		int nsuperburst=(int)psuperburstList.size();
		for(int i=0;i<nsuperburst;i++){
			Csuperburst&superburst=*psuperburstList[i];
			superburst.burst();
	//		if(superburst.isdied)superburst.setVisible(false);
			if(superburst.isdied||superburst.hide||superburst.visible==false)continue;
			//����superburst�ĸ�compball��ɫ
			{
				superburst.updateColorOfcompballs();
			}
		}
		//����psuperburstList�����һ����Ϊdied��superburst
		{
			Csuperburst*psuperburst=NULL;
			for(int i=nsuperburst-1;i>=0;i--){
				Csuperburst&superburst=*psuperburstList[i];
				if(!superburst.isdied){
					psuperburst=&superburst;
					break;
				}
			}//�õ�psuperburst
			if(psuperburst!=NULL){
				//����psuperburst���������ɫ
				float fogColor[4];
				switch(psuperburst->stage){
				case 0:
					init4(fogColor,0.3,0.3,0.4,0.5);
					glFogfv(GL_FOG_COLOR, fogColor);
					glFogf(GL_FOG_DENSITY, 0.0003f);//���Ũ�ȣ�����ָ��ģʽ��
					glass.alpha=0;
					glass.visible=false;
			//		skyball.turnRed=false;
					break;
				case 1:
					init4(fogColor,1,0.5,0,1);
					glFogfv(GL_FOG_COLOR, fogColor);
					glFogf(GL_FOG_DENSITY, 0.00038f);//���Ũ�ȣ�����ָ��ģʽ��
					glass.visible=true;
					glass.alpha=0.25;
			//		skyball.turnRed=true;
					break;
				case 2:
					{
						float k=(psuperburst->timercount-psuperburst->duringTime*0.65)*1.0/(psuperburst->duringTime*(1-0.65)+psuperburst->delayTime);
						init4(fogColor,1+(0.3-1)*k,0.5+(0.3-0.5)*k,0+(0.4-0)*k,1);
						glFogfv(GL_FOG_COLOR, fogColor);
						glFogf(GL_FOG_DENSITY, 0.00038f-0.0001*k);//���Ũ�ȣ�����ָ��ģʽ�� 
						glass.visible=true;
						glass.alpha=0.25+k*(0-0.25);
						
			//			skyball.turnRed=true;
					}
					break;
				}
				
			}
			
		}
	

	}
	//��ը
	{
		int nburst=(int)pburstList.size();
		for(int i=0;i<nburst;i++){
			pburstList[i]->burst();
		}
	}
	//��������
	{
		if(water.visible){//ˮ�ɼ�ʱ����������
			int nbubble=(int)pbubbleList.size();
			for(int i=0;i<nbubble;i++){
				pbubbleList[i]->rise();
			}
		}
	}
	
	
	//Һ����ɢ
	{
		int ndrop=(int)pdropList.size();
		for(int i=0;i<ndrop;i++){
			pdropList[i]->diffuse();
		}
	}
	//�������modelx�Ƶ�����
	{
		float width_mov_modelx=width_mov*0.9;
		float height_mov_modelx=height_mov*0.9;
		float pos_modelx[4];
		modelx.getPosInFather(pos_modelx);
		bool moved=false;
		if(pos_modelx[X]<pos[X]-(width_mov_modelx)/2){
			modelx.movloc_inFather(width_mov_modelx,0,0);
			moved=true;
		}
		if(pos_modelx[Z]<pos[Z]-(height_mov_modelx)/2){
			modelx.movloc_inFather(0,0,height_mov_modelx);
			moved=true;
		}
		if(pos_modelx[X]>pos[X]+(width_mov_modelx)/2){
			modelx.movloc_inFather(-width_mov_modelx,0,0);
			moved=true;
		}
		if(pos_modelx[Z]>pos[Z]+(height_mov_modelx)/2){
			modelx.movloc_inFather(0,0,-height_mov_modelx);
			moved=true;
		}
		if(moved)modelx.downToGround_soft();
		

	}
	//�������tree�Ƶ�����
	{
		int ntree=(int)ptreeList.size();
		for(int i=0;i<ntree;i++){
			Ctree&tree=*ptreeList[i];
			float x=posList_tree[i].v[X];
			float z=posList_tree[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov)/2){
				tree.movloc_inFather(width_mov,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				tree.movloc_inFather(0,0,height_mov);
				moved=true;
			}
			if(x>pos[X]+(width_mov)/2){
				tree.movloc_inFather(-width_mov,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				tree.movloc_inFather(0,0,-height_mov);
				moved=true;
			}
			if(moved){
				float treenewpos[4];
				tree.getPosInFather(treenewpos);
				//��½
				float groundHorizon=ground.getH(treenewpos[X],treenewpos[Z]);
				if(groundHorizon>water.Horizon){
					tree.downToGround(0,false);
				}else{
					tree.downToWaterSurface();
					
				}
			}
			
		}
	}

	int width_mov_molecule=width_mov;
	int height_mov_molecule=height_mov;

	
	//�������amac�Ƶ�����
	{
		int namac=(int)pamacList.size();
		for(int i=0;i<namac;i++){
			Camac&amac=*pamacList[i];
			float x=posList_amac[i].v[X];
			float z=posList_amac[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov_molecule)/2){
				amac.movloc_inFather(width_mov_molecule,0,0);//����0.5��Ϊ����С�ֲ���Χ
				moved=true;
			}
			if(z<pos[Z]-(height_mov_molecule)/2){
				amac.movloc_inFather(0,0,height_mov_molecule);
				moved=true;
			}
			if(x>pos[X]+(width_mov_molecule)/2){
				amac.movloc_inFather(-width_mov_molecule,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov_molecule)/2){
				amac.movloc_inFather(0,0,-height_mov_molecule);
				moved=true;
			}
			if(moved){
				float amacnewpos[4];
				amac.getPosInFather(amacnewpos);
				//��½
				float groundHorizon=ground.getH(amacnewpos[X],amacnewpos[Z]);
				if(groundHorizon>water.Horizon){
					amac.downToGround(20);
				}else{
					amac.downToWaterSurface();
					
				}
			}
			
		}
	}
		//�������can�Ƶ�����
	{
		int ncan=(int)pcanList.size();
		for(int i=0;i<ncan;i++){
			Ccan&can=*pcanList[i];
			float x=posList_can[i].v[X];
			float z=posList_can[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov)/2){
				can.movloc_inFather(width_mov,0,0);//����0.5��Ϊ����С�ֲ���Χ
				moved=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				can.movloc_inFather(0,0,height_mov);
				moved=true;
			}
			if(x>pos[X]+(width_mov)/2){
				can.movloc_inFather(-width_mov,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				can.movloc_inFather(0,0,-height_mov);
				moved=true;
			}
			if(moved){
				can.can.indexOfTextureID=18;
				can.dish.indexOfTextureID=19;
				float cannewpos[4];
				can.getPosInFather(cannewpos);
				//��½
				float groundHorizon=ground.getH(cannewpos[X],cannewpos[Z]);
				if(groundHorizon>water.Horizon){
					can.downToGround(40,true);
				}else{
					can.downToWaterSurface();
					
				}
				can.life=can.lifemax;
			}
			
			
		}
	}
	//amac�ƶ�
	{
		int namac=(int)pamacList.size();
		for(int i=0;i<namac;i++){
			Camac&amac=*pamacList[i];
			if(amac.visible==false)continue;
			if(amac.isOnWater()){
				amac.floatOnWater();
				amac.rotloc010(20/2);
				//�ж���house����ײ
				float amacpos[4];
				amac.getPosInFather(amacpos);
				float e_back[4];
				float d=house.collisionTest_singlePoint(amacpos,amac.Rc,e_back);
				if(d>0){//��ǽ�ڷ�����ײ
					//�ƶ�
					float back[4];
					mul(d,e_back,back);
					amac.movloc_inFather(back[X],back[Y],back[Z]);
					//�ı��ٶ�
					float *v=amac.v;//�����ٶ�
					//�����ٶ�v2=v-2*dot(v,e_back)*e_back
					//��������k=-2*dot(v,e_back)��u=k*e_back����v2=v+u��
					float v2[4];
					float k=-2*dot(v,e_back);
					float u[4];
					mul(k,e_back,u);
					add(v,u,v2);//�õ�v2
					//��v2��дv
					veccopy(v2,v);
				}
			}	
			
		}
	}
	
	//�������ene�Ƶ�����
	{
		int nene=(int)peneList.size();
		for(int i=0;i<nene;i++){
			Cene&ene=*peneList[i];
			float x=posList_ene[i].v[X];
			float z=posList_ene[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov_molecule)/2){
				ene.movloc_inFather(width_mov_molecule,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov_molecule)/2){
				ene.movloc_inFather(0,0,height_mov_molecule);
				moved=true;
			}
			if(x>pos[X]+(width_mov_molecule)/2){
				ene.movloc_inFather(-width_mov_molecule,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov_molecule)/2){
				ene.movloc_inFather(0,0,-height_mov_molecule);
				moved=true;
			}
			if(moved){
				float enenewpos[4];
				ene.getPosInFather(enenewpos);
				//��½
				float groundHorizon=ground.getH(enenewpos[X],enenewpos[Z]);
				if(groundHorizon>water.Horizon){
					ene.downToGround(20);
				}else{
					ene.downToWaterSurface();		
				}
			}
			
		}
	}
	//ene�ƶ�
	{
		int nene=(int)peneList.size();
		for(int i=0;i<nene;i++){
			Cene&ene=*peneList[i];
			if(ene.visible==false)continue;
			if(ene.isOnWater()){
				ene.floatOnWater();
				ene.rotloc010(40/2);
				//�ж���house����ײ
				float enepos[4];
				ene.getPosInFather(enepos);
				float e_back[4];
				float d=house.collisionTest_singlePoint(enepos,ene.Rc,e_back);
				if(d>0){//��ǽ�ڷ�����ײ
					//�ƶ�
					float back[4];
					mul(d,e_back,back);
					ene.movloc_inFather(back[X],back[Y],back[Z]);
					//�ı��ٶ�
					float *v=ene.v;//�����ٶ�
					//�����ٶ�v2=v-2*dot(v,e_back)*e_back
					//��������k=-2*dot(v,e_back)��u=k*e_back����v2=v+u��
					float v2[4];
					float k=-2*dot(v,e_back);
					float u[4];
					mul(k,e_back,u);
					add(v,u,v2);//�õ�v2
					//��v2��дv
					veccopy(v2,v);
				}
			}
		}
	}
	
	//�������gene�Ƶ�����
	{
		int ngene=(int)pgeneList.size();
		for(int i=0;i<ngene;i++){
			Cgene&gene=*pgeneList[i];
			float x=posList_gene[i].v[X];
			float z=posList_gene[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov_molecule)/2){
				gene.movloc_inFather(width_mov_molecule,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov_molecule)/2){
				gene.movloc_inFather(0,0,height_mov_molecule);
				moved=true;
			}
			if(x>pos[X]+(width_mov_molecule)/2){
				gene.movloc_inFather(-width_mov_molecule,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov_molecule)/2){
				gene.movloc_inFather(0,0,-height_mov_molecule);
				moved=true;
			}
			if(moved){
				float genenewpos[4];
				gene.getPosInFather(genenewpos);
				//��½
				float groundHorizon=ground.getH(genenewpos[X],genenewpos[Z]);
				if(groundHorizon>water.Horizon){
					gene.downToGround(20);
				}else{
					gene.downToWaterSurface();
					
				}
			}
			
		}
	}
	//gene�ƶ�
	{
		int ngene=(int)pgeneList.size();
		for(int i=0;i<ngene;i++){
			Cgene&gene=*pgeneList[i];
			if(gene.visible==false)continue;
			if(gene.isOnWater()){
				gene.floatOnWater();
				//�ж���house����ײ
				float genepos[4];
				gene.getPosInFather(genepos);
				float e_back[4];
				float d=house.collisionTest_singlePoint(genepos,gene.Rc,e_back);
				if(d>0){//��ǽ�ڷ�����ײ
					//�ƶ�
					float back[4];
					mul(d,e_back,back);
					gene.movloc_inFather(back[X],back[Y],back[Z]);
					//�ı��ٶ�
					float *v=gene.v;//�����ٶ�
					//�����ٶ�v2=v-2*dot(v,e_back)*e_back
					//��������k=-2*dot(v,e_back)��u=k*e_back����v2=v+u��
					float v2[4];
					float k=-2*dot(v,e_back);
					float u[4];
					mul(k,e_back,u);
					add(v,u,v2);//�õ�v2
					//��v2��дv
					veccopy(v2,v);
				}
			}
		}
	}
	
	//�������autoCell�Ƶ�����
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			float x=posList_autoCell[i].v[X];
			float z=posList_autoCell[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov)/2){
				autoCell.movloc_inFather(width_mov,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				autoCell.movloc_inFather(0,0,height_mov);
				moved=true;
			}
			if(x>pos[X]+(width_mov)/2){
				autoCell.movloc_inFather(-width_mov,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				autoCell.movloc_inFather(0,0,-height_mov);
				moved=true;
			}
		}
	}
	
	//�������arch�Ƶ�����
	{
		int narch=(int)parchList.size();
		for(int i=0;i<narch;i++){
			Carch&arch=*parchList[i];
			float x=arch.x;
			float z=arch.z;
			bool needreform=false;
			if(x<pos[X]-(width_mov)/2){
				arch.movloc_inFather(width_mov,0,0);
				arch.storexz(arch.x+width_mov,arch.z);
				needreform=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				arch.movloc_inFather(0,0,height_mov);
				arch.storexz(arch.x,arch.z+height_mov);
				needreform=true;
			}
			if(x>pos[X]+(width_mov)/2){
				arch.movloc_inFather(-width_mov,0,0);
				arch.storexz(arch.x-width_mov,arch.z);
				needreform=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				arch.movloc_inFather(0,0,-height_mov);
				arch.storexz(arch.x,arch.z-height_mov);
				needreform=true;
			}
			//�ؽ�arch
			if(needreform){
				//�ָ�����
				arch.life=arch.lifemax;
				//
				Cstick&stick0=*arch.pstickList[0];
				Cstick&stick1=*arch.pstickList[1];
				Cstick&stick2=*arch.pstickList[2];
				Cstick&stick3=*arch.pstickList[3];
				Cstick&stick4=*arch.pstickList[4];
				Cstick&stick5=*arch.pstickList[5];
				//��λ
				makeE(stick0.RMmat);
				makeE(stick1.RMmat);
				makeE(stick2.RMmat);
				makeE(stick3.RMmat);
				makeE(stick4.RMmat);
				makeE(stick5.RMmat);
				//��Ϊ����
				arch.setfreeze(true);
				//�ֲ���λ
				stick0.setPosInFather(100,0,0);
				stick1.setPosInFather(-100,0,0);
				stick3.setPosInFather(0,0,100);
				stick4.setPosInFather(0,0,-100);
				//ȫ�ֶ�λ
				float x=arch.x;
				float z=arch.z;
				//�Ƶ�Ŀ��λ��
				stick0.movloc(x,0,z);
				stick1.movloc(x,0,z);
				stick3.movloc(x,0,z);
				stick4.movloc(x,0,z);
				//�����߶�
				stick0.downToGround(stick0.len()/2,true);
				stick1.downToGround(stick1.len()/2,true);
				stick3.downToGround(stick3.len()/2,true);
				stick4.downToGround(stick4.len()/2,true);
				//����λ��
				//stick2��λ��
				{
					float head0[4];
					stick0.toFather(0,stick0.len()/2+stick0.d/2,0,1,head0);
					float head1[4];
					stick1.toFather(0,stick1.len()/2+stick1.d/2,0,1,head1);
					float half[4];
					add(head0,head1,half);
					mul(0.5,half,half);
					stick2.setPosInFather(half[X],half[Y],half[Z]);
					float vec[4];
					sub(head0,head1,vec);
					normalize(vec);
					stick2.setPosture_inFather(vec);
				}
				//stick5��λ��
				{
					float head3[4];
					stick3.toFather(0,stick3.len()/2+stick3.d/2,0,1,head3);
					float head4[4];
					stick4.toFather(0,stick4.len()/2+stick4.d/2,0,1,head4);
					float half[4];
					add(head3,head4,half);
					mul(0.5,half,half);
					stick5.setPosInFather(half[X],half[Y],half[Z]);
					float vec[4];
					sub(head4,head3,vec);
					normalize(vec);
					stick5.setPosture_inFather(vec);
				}	
			}
			if(showShadow){
				arch.mesh2mesh_world();
				arch.remakeBondEdgeList(light_pos);
				arch.remakeSV(light_pos);
			}
			
		}
	}
	//autoCell��½
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			float x=posList_autoCell[i].v[X];
			float z=posList_autoCell[i].v[Z];
			//��½
			float groundHorizon=ground.getH(x,z);
		
			if(groundHorizon>water.Horizon){
				autoCell.downToGround_soft(0.5/3,20);
			}else{
				autoCell.downToWaterSurface_soft(0.5/3);
			}
		
			
		}
	}

	


	//autoCellת��
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.visible==false)continue;
			//����ת��
			if(!autoCell.isOnWater()){//��½��
				autoCell.smartRot(*pcell,false);
			}else{//��ˮ��
				autoCell.smartRot(*pcell,true);
			}
		}
	}
	//autoCellǰ��
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			//ǰ��
			if(!autoCell.isOnWater()){//��½��
				autoCell.advance(*pcell,false);
			}else{//��ˮ��
				autoCell.advance(*pcell,true);
			}
			if(autoCell.visible==false)continue;//������ɼ���ֻǰ�����ɣ�������ײ���
			float *autoPos=posList_autoCell[i].v;//���ڲ�Ҫ��ܾ�ȷ�ļ�⣬ֱ����autoCell����λ�ü���
			//����λ����house������ײ���
			float e_back[4];//��������
			float d=house.collisionTest_singlePoint(autoPos,autoCell.Rc,e_back);//�������
			if(d>0){//��house������ײ
				//����
				float back[4];//��������
				mul(d,e_back,back);
				autoCell.movloc_inFather(back[X],back[Y],back[Z]);
				//��autoCell��ǰ�������Ϊ��ǽ��ƽ��
				//��autoCell�ĵ�ǰ��������
				float curdir[4];//��ǰ��������
				autoCell.toFather(0,0,-1,0,curdir);
				//��autoCell����λ��
				//����ǽ��ƽ�е���������autoCell��Ŀ�곯������
				float tgdir[4];//Ŀ�곯��������tgdir=(back x curdir) x back
				float updn[4];
				cross(back,curdir,updn);
				cross(updn,back,tgdir);
				tgdir[Y]=0;//����б
				if(normalize(tgdir)==0){//�����0����
					//˵��curdir��tgdir���ߣ����õ���
				}else{//�õ�tgdir
					//��������Ϊtgdir
					autoCell.setPostureWidthWantedDir_inFather(tgdir);
				}
			}
			
		}
	}
	//��ÿ��autoCell��ʱ
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			pautoCellList[i]->countTime();
		}
	}
	//ÿ��autoCell�䶯
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			if(pautoCellList[i]->visible)pautoCellList[i]->wri();
		}
	}
	//--------------------ʱ��-------------------------------------------------
	//arch��ʱ��
	{
		int narch=(int)parchList.size();
		for(int i=0;i<narch;i++){
			Carch&arch=*parchList[i];
			arch.timer_adjust_run();
		}
	}
	
	//---------------------�����˶�---------------------------------------------
	//proteinת��
	protein.rotloc100(10);
	protein.rotloc010(15);
	//��պи���
	skyball.setPosInFather(pos[X],pos[Y],pos[Z]);
	//ˮ��
	//��water.Horizon����waterHorizon�ƶ�
	water.Horizon+=(waterHorizon-water.Horizon)*0.1;
	//ˮ������
	if(water.visible)water.wave();
	if(waterBox.visible)waterBox.wave(0.8,0.55);
	
	//ʵ��water�����ǵĸ���Ϊ�˱�֤ˮ������ͼ����ȷ����Զ��߽���ƽ��
	float water_to_cell[4];
	sub(pos,pos_water,water_to_cell);
	//����ƽ������
	float dx;
	float dz;
	dx=water_to_cell[X];
	dz=water_to_cell[Z];
	water.movRect(dx,dz);
	
	//-------------------����----------------------------------------------------

	//����
	if(aKeyDown){
		if(!pcell->jump){//���û���𣬲ſ�����
			pcell->startJump(55);
		}
	}
	//���house�컨��߶�
	float houseCeilH=house.getH_ceil(pos);
	//���house���棬���棬ˮ�������߶�
	float groundHorizon=ground.getH(pos[X],pos[Z]);
	float houseHorizon=house.getH_floor(pos);
	float waterHorizon=water.Horizon;
	//pcell����Ӧ����ĸ߶�
	float H0=30;
	//*pcell��������
	if(pcell->jump){
		pcell->fall();
		//������������
		pcell->getPosInFather(pos);
		//�ж��Ƿ�Ӵ��컨��
		if(pos[Y]+H0>houseCeilH){
			pcell->vup=-20;//Ϊ�˲����컨�巢����ճ𤡱�����ǽ�vup��Ϊ0��������Ϊһ����ֵ������һ�����µĳ��ٶȣ�
			pcell->setPosInFather(pos[X],houseCeilH-H0-10,pos[Z]);
			pos[Y]=houseCeilH-H0-10;//Ϊ�˺��漸���жϵ���ȷ����pos[Y]ͬ������
		}
		//�ж��Ƿ�Ӵ�����
		else if(pos[Y]-H0<=groundHorizon){
			pcell->jump=false;
			//����˴�ˮ��ߣ�˵�����䵽ˮ���ˣ���Ҫ��������ˮ�е�����
			if(waterHorizon>groundHorizon){
				//��������
				alSource3f(source_fall_in_water, AL_POSITION, pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
				//����fabs(vup)�Ĵ�С��������
				float a,b;
				calLinearModel(15,0.05,87,1,a,b);
				float gain=a*fabs(pcell->vup)+b;
				gain=min(1,gain);//����gain������1
				alSourcef(source_fall_in_water,AL_GAIN,gain);
				//����
				alSourcePlay(source_fall_in_water);
			}

		}
		//�ж��Ƿ�Ӵ�house����
		else if(pos[Y]-H0<=houseHorizon){
			pcell->jump=false;
			if(waterHorizon>houseHorizon){
				//��������
				alSource3f(source_fall_in_water, AL_POSITION, pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
				//����fabs(vup)�Ĵ�С��������
				float a,b;
				calLinearModel(15,0.05,87,1,a,b);
				float gain=a*fabs(pcell->vup)+b;
				gain=min(1,gain);//����gain������1
				alSourcef(source_fall_in_water,AL_GAIN,gain);
				//����
				alSourcePlay(source_fall_in_water);
			}
		}
		
	}
	
	int onWhich=0;//onWhich==0Ϊ��ˮ�棬onWhich==1Ϊ�ڵ��棬onWhich==2Ϊ��house����
	
	//��*pcell�ĸ߶ȵ���Ϊmax(house����,����,ˮ��)
	if(pcell->jump==false){//������ʱ�����ڵ���
		//��pcellλ��
		float pos[4];
		pcell->getPosInFather(pos);
		//��house���棬���棬ˮ�����߸߶ȵ����ֵ����pcell��ǰ�߶Ƚ��бȽ�
		float Hmax=max(houseHorizon,max(groundHorizon,waterHorizon));
		if(pos[Y]>Hmax+H0+10){//���ֹͣ����ʱ���ڼ������»�û���ŵأ������һ����΢����
			//Ϊ��ʹ��jumpable==falseʱҲ�������ƹ�startJumpֱ���ֶ����ã�������pcell->startJump(5);
			pcell->vup=5;
			pcell->jump=true;
		}else{
			//�ж����ǵ�ǰλ����house����߻���ˮ��߻��ǵ����
			if(houseHorizon>groundHorizon&&houseHorizon>waterHorizon){//house�������
				pcell->setPosInFather(pos[X],houseHorizon+H0,pos[Z]);
				float norm[4]={0,1,0,1};
				pcell->setPosture_inFather_soft(norm);
				onWhich=2;
			}else{//����house�������
				if(groundHorizon>waterHorizon){//�������
					if(pcell->bspeedup)pcell->downToGround_soft(0.65/3,20);
					else pcell->downToGround_soft(0.5/3,20);
					onWhich=1;
				}else{//ˮ�����
					pcell->downToWaterSurface_soft(0.5/3);
					onWhich=0;
					
				}
			}
		}
	}//�õ�onWhich
	
	
	
	//*pcell��ɫ
	if(pcell->nomatch){
		int rd=timecounter%4;
		if(rd==0||rd==1){
			pcell->core.indexOfTextureID=2;
		}else if(rd==2||rd==3){
			pcell->core.indexOfTextureID=4;
		}
	}else{//��nomatchʱһ��Ҫ��֤���Ǻ��
		pcell->core.indexOfTextureID=2;
		
	}
	//*pcell������ʱ�Ӹ���
	pcell->timerscount();
	
	//*pcell�䶯
	pcell->wri();
	
	//�����ڵ�
	if(dKeyDown){
		if(timecounter%3==0){
			pcell->fire();
			alSource3f(source_gun_small, AL_POSITION, pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
			alSourcePlay(source_gun_small);
		}
	}
	
	
	//�ڵ��˶�
	pcell->cannonballsMov();
	//----------------------------------------------*pcell�ƶ�
	//�ƶ�ǰ����pcell��RTmat
	float RMmat[16];
	matcopy(pcell->RMmat,RMmat);
	//�ƶ�
	pcell->bmoving=false;
	if(upKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->movloc_pushWater(0,0,-pcell->getVlen());
		}else{
			pcell->movloc(0,0,-pcell->getVlen());
		}
		pcell->bmoving=true;
		
		
	}
	if(downKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->movloc_pushWater(0,0,pcell->getVlen());
		}else{
			pcell->movloc(0,0,pcell->getVlen());
		}
		pcell->bmoving=true;
		
	}
	//���source_move_on_ground��source_move_on_water�Ĳ���״̬
	ALint state_move_on_ground;
	ALint state_move_on_water;
	alGetSourcei(source_move_on_ground, AL_SOURCE_STATE,&state_move_on_ground);
	alGetSourcei(source_move_on_water, AL_SOURCE_STATE,&state_move_on_water);

	if(pcell->bmoving==true&&pcell->jump==false){//����ƶ���δ����
		if(onWhich==1||onWhich==2){//����ڵ����house����
			if(state_move_on_water==AL_PLAYING){//ֹͣsource_move_on_water
				alSourceStop(source_move_on_water);
				//���Ź�����
				alSource3f(source_water_gulu,AL_POSITION,pos[X]*k_soundDis,waterHorizon*k_soundDis,pos[Z]*k_soundDis);
				alSourcePlay(source_water_gulu);
			}
			if(state_move_on_ground!= AL_PLAYING){//���source_move_on_ground��ֹͣ�����ٴ�����
				alSourcePlay(source_move_on_ground);
			}
			//������Դλ��
			alSource3f(source_move_on_ground,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
		}else if(onWhich==0){//�����ˮ��
			if(state_move_on_ground==AL_PLAYING)alSourceStop(source_move_on_ground);//ֹͣsource_move_on_ground
			//���source_move_on_water��״̬
			if(state_move_on_water!= AL_PLAYING){//���source_move_on_water��ֹͣ�����ٴ�����
				alSourcePlay(source_move_on_water);
			}
			//������Դλ��
			alSource3f(source_move_on_water,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
			

		
		}

	}else{//�������
		if(state_move_on_ground==AL_PLAYING)alSourceStop(source_move_on_ground);//ֹͣsource_move_on_ground
		if(state_move_on_water==AL_PLAYING){//ֹͣsource_move_on_water
			alSourceStop(source_move_on_water);
			//���Ź�����
			alSource3f(source_water_gulu,AL_POSITION,pos[X]*k_soundDis,waterHorizon*k_soundDis,pos[Z]*k_soundDis);
			alSourcePlay(source_water_gulu);
		}
		

	}
	//------------------------------*pcell�ƶ���ִ�����뾲̬�������ײ��⣬�����ײ����ָ�
	//ȡ��pcell�ƶ����������
	pcell->getPosInFather(pos);
	//pcell��house����ײ
	float e_back[4];
	float d=house.collisionTest_multiPoint_pcell(pos,pcell->Rc,e_back);
	if(d>0){
		//�ָ�
		matcopy(RMmat,pcell->RMmat);
		float back[4];
		mul(d*0.2,e_back,back);
		back[Y]=0;
		pcell->movloc_inFather(back[X],back[Y],back[Z]);
	}
	
	
	
	//*pcell��tree��ײ��ʹ���������
	{
		//�����ײ�б�
		float *pos1=pos;
		float R1=pcell->Rc;
		myvector<int> clist;
		treeCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];//�±��
			Ctree&tree=*ptreeList[I];	
			if(tree.visible==false)continue;
			//���tree��myCell����ײ
			float *pos2=posList_tree[I].v;//treeλ��
			float R2=tree.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<pow2(R1+R2)){//myCell��tree��ײ
				//����
				float k=0.25;
				float backLen=((R1+R2)-CarmSqrt(dis2))*k;//��ײ�ķ�����ȵ�k��������ˣ�
				float back[4];//��������
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
				if(normalize(back)==0)continue;
				mul(backLen,back,back);
				back[Y]=0;//����Y����
				//��back����
				pcell->movloc_inFather(back[X],back[Y],back[Z]);
				break;
			}
			
		}
	}
	
	//pcell��protein����ײ���
	if(protein.visible){
		float R1=pcell->Rc;
		float R2=protein.Rc;
		float *pos1=pos;
		float pos2[4];//protein������
		protein.getPosInFather(pos2);
		if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<pow2(R1+R2)
			&&fabs(pos1[Y]-pos2[Y])<R2+R1/6){//��ײ
			//protein��ʧ
			protein.visible=false;
			missionDone=true;
			//����mission_done��Ч
			{
				alSource3f(source_mission_done,AL_POSITION,pos1[X]*k_soundDis,pos1[Y]*k_soundDis,pos1[Z]*k_soundDis);//��pos1������pos2
				alSourcePlay(source_mission_done);
			}
		}
	}
	//----------------------------------------------------*pcell��ת
	if(leftKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->rotloc_pushWater_010(7.0);
		}else{
			pcell->rotloc010(7.0);
		}
		pcell->bmoving=true;
	}
	if(rightKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->rotloc_pushWater_010(-7.0);
		}else{
			pcell->rotloc010(-7.0);
		}
		pcell->bmoving=true;
	}
	//-----------ɾ���������Ϊ����Ϊ�˷�ֹgridʧЧ---------------------------------
	//-----------�����б���ѭ���г��ȷ����仯�����������Ͻ���ǰ�̻�����ѭ������Ӧ��n--
	//��life��Ϊ0��autoCellɾ��
	{
		int nautoCell=(int)pautoCellList.size();
		int count=0;
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.life<=0){
				//���ǻ�÷���
				pcell->score+=10;
				//�ӳ�������ժ����
				ground.ridchild(&autoCell);
				//���뵽�����о��б�
				pdiedautoCellList.push_back(&autoCell);
				count++;
			}else{
				if(count!=0)pautoCellList[i-count]=&autoCell;
			}
		}
		pautoCellList.resize(nautoCell-count);
	}
	//����pdiedautoCellList�ĳ���
	{
		const int maxLen=10;//pdiedautoCellList������Ƴ���
		int ndiedautoCell=(int)pdiedautoCellList.size();
		if(ndiedautoCell>maxLen){
			//��pdiedautoCellList��������ΪmaxLen_pautoCellList
			int ncut=ndiedautoCell-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedautoCellList[ndiedautoCell-i];
				pdiedautoCellList.pop_back();
			}
		}
	}
	//�����Ϊdisapear���ڵ�ɾ��
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		int count=0;
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			if(cannonball.isdisapear()){
				ground.ridchild(&cannonball);//���ڵ��ӳ�������ȡ��
				delete &cannonball;//ɾ���ڵ�����
				count++;
			}else{
				if(count!=0)pcell->pcannonballList[i-count]=&cannonball;
			}
		}
		pcell->pcannonballList.resize(ncannonball-count);
	}
	//�����Ϊdisapear��amacɾ��
	{
		int namac=(int)pamacList.size();
		int count=0;
		for(int i=0;i<namac;i++){
			Camac&amac=*pamacList[i];
			if(amac.isdisapear()){
				//�ӳ�������ժ����
				ground.ridchild(&amac);
				//ɾ��
				delete pamacList[i];
				count++;
			}else{
				if(count!=0)pamacList[i-count]=&amac;
				
			}
		}
		pamacList.resize(namac-count);
	}
	//�����Ϊdisapear��eneɾ��
	{
		int nene=(int)peneList.size();
		int count=0;
		for(int i=0;i<nene;i++){
			Cene&ene=*peneList[i];
			if(ene.isdisapear()){
				//�ӳ�������ժ����
				ground.ridchild(&ene);
				//ɾ��
				delete peneList[i];
				count++;
			}else{
				if(count!=0)peneList[i-count]=&ene;
			}
		}
		peneList.resize(nene-count);
	}
	//�����Ϊdisapear��geneɾ��
	{
		int ngene=(int)pgeneList.size();
		int count=0;
		for(int i=0;i<ngene;i++){
			Cgene&gene=*pgeneList[i];
			if(gene.isdisapear()){
				//�ӳ�������ժ����
				ground.ridchild(&gene);
				//ɾ��
				delete pgeneList[i];
				count++;
			}else{
				if(count!=0)pgeneList[i-count]=&gene;
			}
		}
		pgeneList.resize(ngene-count);
	}
	
	//����ѽ���������
	{
		int nbubble=(int)pbubbleList.size();
		int count=0;
		for(int i=0;i<nbubble;i++){
			Cbubble&bubble=*pbubbleList[i];
			if(bubble.isdied){
				//�ӳ�������ժ����
				ground.ridchild(&bubble);
				//ɾ��
				delete pbubbleList[i];
				count++;
			}else{
				if(count!=0)pbubbleList[i-count]=&bubble;
			}
		}
		pbubbleList.resize(nbubble-count);
	}
	//����ѽ�����Һ��
	{
		int ndrop=(int)pdropList.size();
		int count=0;
		for(int i=0;i<ndrop;i++){
			Cdrop&drop=*pdropList[i];
			if(drop.isdied){
				//�ӳ�������ժ����
				ground.ridchild(&drop);
				//ɾ��
				delete pdropList[i];
				count++;
			}else{
				if(count!=0)pdropList[i-count]=&drop;
			}
		}
		pdropList.resize(ndrop-count);
	}
		//���ѽ�����atomburst����pdiedatomburstList�б�
	{
		int natomburst=(int)patomburstList.size();
		int count=0;
		for(int i=0;i<natomburst;i++){
			Catomburst&atomburst=*patomburstList[i];
			if(atomburst.isdied){
				//�ӳ�������ժ����
				ground.ridchild(&atomburst);
				//���뵽pdiedatomburstList��
				pdiedatomburstList.push_back(&atomburst);
				count++;
			}else{
				if(count!=0)patomburstList[i-count]=&atomburst;
			}
		}
		patomburstList.resize(natomburst-count);
	}
	//����pdiedatomburstList�ĳ���
	{
		const int maxLen=6;//pdiedatomburstList������Ƴ���
		int ndiedatomburst=(int)pdiedatomburstList.size();
		if(ndiedatomburst>maxLen){
			//��pdiedatomburstList��������ΪmaxLen
			int ncut=ndiedatomburst-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedatomburstList[ndiedatomburst-i];
				pdiedatomburstList.pop_back();
			}
		}
	}
	//��visible==false��bigcannon����pdiedbigcannonList�б�
	{
		int nbigcannon=(int)pbigcannonList.size();
		int count=0;
		for(int i=0;i<nbigcannon;i++){
			Cbigcannon&bigcannon=*pbigcannonList[i];
			if(bigcannon.visible==false){
				//�ӳ�������ժ����
				ground.ridchild(&bigcannon);
				//���뵽pdiedbigcannonList��
				pdiedbigcannonList.push_back(&bigcannon);
				count++;
			}else{
				if(count!=0)pbigcannonList[i-count]=&bigcannon;
			}
		}
		pbigcannonList.resize(nbigcannon-count);
	}
	//����pdiedbigcannonList�ĳ���
	{
		const int maxLen=15;//pdiedbigcannonList������Ƴ���
		int ndiedbigcannon=(int)pdiedbigcannonList.size();
		if(ndiedbigcannon>maxLen){
			//��pdiedbigcannonList��������ΪmaxLen
			int ncut=ndiedbigcannon-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedbigcannonList[ndiedbigcannon-i];
				pdiedbigcannonList.pop_back();
			}
		}
	}
	//���ѽ�����superburstɾ��
	{
		int nsuperburst=(int)psuperburstList.size();
		int count=0;
		for(int i=0;i<nsuperburst;i++){
			Csuperburst&superburst=*psuperburstList[i];
			if(superburst.isdied){
				//�ӳ�������ժ����
				ground.ridchild(&superburst);
				count++;
			}else{
				if(count!=0)psuperburstList[i-count]=&superburst;
			}
		}
		psuperburstList.resize(nsuperburst-count);
	}
	//���ѽ�����burst����pdiedburstList�б�
	{
		int nburst=(int)pburstList.size();
		int count=0;
		for(int i=0;i<nburst;i++){
			Cburst&burst=*pburstList[i];
			if(burst.isdied){
				//�ӳ�������ժ����
				ground.ridchild(&burst);
				//���뵽pdiedburstList��
				pdiedburstList.push_back(&burst);
				count++;
			}else{
				if(count!=0)pburstList[i-count]=&burst;
			}
		}
		pburstList.resize(nburst-count);
	}
//	cout<<pdiedburstList.size()<<endl;
	//����pdiedburstList�ĳ���
	{
		const int maxLen=20;//pdiedburstList������Ƴ���
		int ndiedburst=(int)pdiedburstList.size();
		if(ndiedburst>maxLen){
			//��pdiedburstList��������ΪmaxLen_pburstList
			int ncut=ndiedburst-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedburstList[ndiedburst-i];
				pdiedburstList.pop_back();
			}
		}
	}
	//-------------���ӷ������Ϊ�˷�ֹgridʧЧ-----------------------------
	//��������
	if((int)pbubbleList.size()<10){
		//�����������
		int x=pos[X]+(rand()%(int)areaWidth_god-areaWidth_god/2)*0.5;
		int z=pos[Z]+(rand()%(int)areaHeight_god-areaHeight_god/2)*0.5;
		//��������θ��ǣ�������bubble������
		float groundHorizon=ground.getH(x,z);
		if(groundHorizon<water.Horizon){//��ˮ�棬��������
			//����bubble
			Cbubble*pbubble=new Cbubble();
			pbubble->movloc(x,groundHorizon,z);
			pbubble->bubble.indexOfTextureID=9;
			ground.addchild(pbubble);
			pbubbleList.push_back(pbubble);
			//�������
			if(rand()%4==0){//����������ô�ܼ�
				pbubble->sourceMake(4);
				pbubble->sourceGain(0.2);
				pbubble->sourcePos(x,groundHorizon,z,k_soundDis);
				pbubble->sourcePlay();
			}

		}
	}
	//����Һ��
	if((int)pdropList.size()<5){
		//��������
		int x=pos[X]+(rand()%(int)(areaWidth_god)-areaWidth_god/2)*0.6;
		int z=pos[Z]+(rand()%(int)(areaHeight_god)-areaHeight_god/2)*0.6;
		//�ж����ڵ��滹����ˮ��
		float groundHorizon=ground.getH(x,z);
		if(groundHorizon<water.Horizon){//��ˮ�棬����Һ��
			pdropList.grow();
			pdropList[(int)pdropList.size()-1]=new Cdrop();
			Cdrop&drop=*pdropList[(int)pdropList.size()-1];
			int colorIndex=rand()%(int)dropColorList.size();
			float R=dropColorList[colorIndex].R;
			float G=dropColorList[colorIndex].G;
			float B=dropColorList[colorIndex].B;
			drop.drop.setColour(R,G,B,1);
			drop.drop.indexOfTextureID=8;
			drop.movloc(x,waterHorizon,z);
			//���뵽������
			ground.addchild(&drop);
			drop.setGround(&ground);
		}
		
	}
	//������һЩ��������Ķ��������ڷ�Ƶ�����
	switch(timecounter%20)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		//������autoCell��ά��autoCell����ΪNautoCell
		if((int)pautoCellList.size()<NautoCell){
			//���pdiedautoCellList����Ԫ�أ�������ó�һ����������
			int ndiedautoCell=(int)pdiedautoCellList.size();
			if(ndiedautoCell!=0){//��Ԫ�أ�ѭ������
				//��pdiedautoCellList���ó�һ��Ԫ��
				//���ѡȡ
				int I=rand()%ndiedautoCell;
				CautoCell*pautoCell=pdiedautoCellList[I];
				//��pautoCell���³�ʼ��
				const int vlen=15/3;//������ϸ���ٶ��ѷ����˱仯�������ٶ������³�ʼ��
				int A=rand()*piDiv180;
				float vx=vlen*fastcos_LP(A);
				float vz=vlen*fastsin_LP(A);
				pautoCell->setV(vx,0,vz);
				int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
				int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
				pautoCell->movloc(x,0,z);
				pautoCell->bflglr=false;//�ޱ�ë
				pautoCell->bshell=false;//�޿�
				pautoCell->foot=false;//�޽ţ��нŵ��Ǹ��㣬ֻ��û����ɫ��
				pautoCell->knee=false;//��ϥ����ϥ���Ǹ��㣬ֻ��û����ɫ��
				pautoCell->timecount=0;
				pautoCell->life=2;
				ground.addchild(pautoCell);
				//��½
				float groundHorizon=ground.getH(x,z);
				if(groundHorizon>water.Horizon){
					pautoCell->downToGround(20);
				}else{
					pautoCell->downToWaterSurface();
					
				}
				//��pautoCell���뵽pautoCellList
				pautoCellList.push_back(pautoCell);
				//��pdiedautoCellList�����һ��Ԫ��ȥ����λ��I�ϵĿ�ȱ
				//Ȼ��pdiedautoCellList�����һ��Ԫ��ɾ��
				if(ndiedautoCell==1){//���ԭ��pdiedautoCellList��ֻ��һ��Ԫ�أ����ò����ȱ��
					//ֱ�ӽ����һ��Ԫ��ɾ��
					pdiedautoCellList.pop_back();
				}else{//���������һ��Ԫ�ز���I�ϵĿ�ȱ����ɾ�����һ��Ԫ��
					pdiedautoCellList[I]=pdiedautoCellList[ndiedautoCell-1];
					pdiedautoCellList.pop_back();
				}
			}else{//pdiedautoCellList��û��Ԫ�أ��޷�ѭ�����ã�ֻ�����½�autoCell
				pautoCellList.grow();
				pautoCellList[(int)pautoCellList.size()-1]=new CautoCell();
				CautoCell&autoCell=*pautoCellList[(int)pautoCellList.size()-1];
				autoCell.indexOfTextureID=5;
				autoCell.core.indexOfTextureID=6;
				autoCell.movloc(0,40,0);
				const int vlen=15/3;
				int A=rand()*piDiv180;
				float vx=vlen*fastcos_LP(A);
				float vz=vlen*fastsin_LP(A);
				autoCell.setV(vx,0,vz);
				int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
				int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
				autoCell.movloc(x,0,z);
				ground.addchild(&autoCell);
				autoCell.setGround(&ground);
				autoCell.setWater(&water);
				init4(autoCell.flglrcolor,70.0/255,1,70.0/255,1);
				autoCell.zoomloc0(0.45,0.45,0.45);
				autoCell.indexOfTextureID=3;
				autoCell.setRc(Rc_autoCell);
				//		autoCell.bshowBB=true;
				autoCell.core.indexOfTextureID=4;
				autoCell.bmoving=true;
				//��½
				float groundHorizon=ground.getH(x,z);
				if(groundHorizon>water.Horizon){
					autoCell.downToGround(20);
				}else{
					autoCell.downToWaterSurface();
					
				}
			}
		}
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		//������amac��ά������ΪNamac
		if((int)pamacList.size()<Namac){
			pamacList.grow();
			pamacList[(int)pamacList.size()-1]=new Camac();
			Camac&amac=*pamacList[(int)pamacList.size()-1];
			int vlen=30/3;
			int A=rand()*piDiv180;
			float vx=vlen*fastcos_LP(A);
			float vz=vlen*fastsin_LP(A);
			amac.setV(vx,0,vz);
			int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
			int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
			amac.movloc(x,0,z);
			amac.zoomloc(3,3,3);
			ground.addchild(&amac);
			amac.setGround(&ground);
			amac.setWater(&water);
			//   	amac.bshowBB=true;
			amac.setRc(Rc_amac);
			amac.rotloc010(rand());
			//��½
			float groundHorizon=ground.getH(x,z);
			if(groundHorizon>water.Horizon){
				amac.downToGround(20);
			}else{
				amac.downToWaterSurface();
				
			}
			
		}
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		//������gene��ά������ΪNgene
		if((int)pgeneList.size()<Ngene){
			pgeneList.grow();
			pgeneList[(int)pgeneList.size()-1]=new Cgene();
			Cgene&gene=*pgeneList[(int)pgeneList.size()-1];
			int vlen=30/3;
			int A=rand()*piDiv180;
			float vx=vlen*fastcos_LP(A);
			float vz=vlen*fastsin_LP(A);
			gene.setV(vx,0,vz);
			int x=pos[X]+rand()%(int)areaWidth_god-areaWidth_god/2;
			int z=pos[Z]+rand()%(int)areaHeight_god-areaHeight_god/2;
			gene.movloc(x,0,z);
			gene.zoomloc(3,3,3);
			ground.addchild(&gene);
			gene.setGround(&ground);
			gene.setWater(&water);
			//		gene.bshowBB=true;
			gene.setRc(Rc_gene);
			//��ɫ
			int colorflg=rand()%7;
			switch(colorflg){
			case 0://����ȫ�����
			case 1:
				{
					gene.effectID=1;
					for(int i=0;i<=5;i++)gene.ball[i].setColour(1,0,0,1);
				}
				break;
			case 2://����ȫ�̻���
				{
					gene.effectID=2;
					for(int i=0;i<=5;i++)gene.ball[i].setColour(0,1,0,1);
				}
				break;
			case 3://����ȫ������
			case 4:
				{
					gene.effectID=3;
					for(int i=0;i<=5;i++)gene.ball[i].setColour(0,0,1,1);
				}
				break;
			default://������ɸ�����ɫ�������뱣֤������ͬɫ
				{
					gene.effectID=0;
					//������ɸ�����ɫ
					for(int i=0;i<=5;i++){
						int index=rand()%3;
						switch(index){
						case 0:
							gene.ball[i].setColour(1,0,0,1);
							break;
						case 1:
							gene.ball[i].setColour(0,1,0,1);
							break;
						case 2:
							gene.ball[i].setColour(0,0,1,1);
							break;
						}
					}
					//�ٱ�֤��������ȫͬɫ
					int index=rand()%5;//����0,1,2,3,4��һ����
					//ǿ��gene.ball[index]��gene.ball[5]��ͬɫ
					float r=gene.ball[5].colour[0];
					float g=gene.ball[5].colour[1];
					float b=gene.ball[5].colour[2];
					gene.ball[index].setColour(b,r,g,1);//��ͱ�֤�����߲�ͬɫ
				}
				break;
			}
			
			//��½
			float groundHorizon=ground.getH(x,z);
			if(groundHorizon>water.Horizon){
				gene.downToGround(20);
			}else{
				gene.downToWaterSurface();
				
			}
			
		}
		break;
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		//������ene��ά������ΪNene
		if((int)peneList.size()<Nene){
			peneList.grow();
			peneList[(int)peneList.size()-1]=new Cene();
			Cene&ene=*peneList[(int)peneList.size()-1];
			int vlen=30/3;
			int A=rand()*piDiv180;
			float vx=vlen*fastcos_LP(A);
			float vz=vlen*fastsin_LP(A);
			ene.setV(vx,0,vz);
			int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
			int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
			ene.movloc(x,0,z);
			ene.zoomloc(3,3,3);
			ground.addchild(&ene);
			ene.setGround(&ground);
			ene.setWater(&water);
			//	ene.bshowBB=true;
			ene.setRc(Rc_ene);
			ene.rotloc010(rand());
			//��½
			float groundHorizon=ground.getH(x,z);
			if(groundHorizon>water.Horizon){
				ene.downToGround(20);
			}else{
				ene.downToWaterSurface();
				
			}
			
		}
		break;
	}
	//-------------------------------����λ�úͷ���
	//�˲������������Ϊ����ɾ����һЩ�������λ���б�ͳ����б�������
	updatePosAndDir();
	//-----------------------------����LOD�ȼ�����߿��
	//����һ���ĳٻ�����һ����Ƶ
	//������updatePosAndDir��Ȼ�����updateLODlevelAndPointOrLineSize
	//������ܵ���posList������б���Ӧ�������ǵ�������Ҳ����Ӧ�����������
	updateLODlevelAndPointOrLineSize();
	//-------------------------------------------------------
	if(cheating){
		pcell->Ngun=4;
		pcell->ene[0].setColour(0,1,0,1);
		pcell->ene[1].setColour(0,1,0,1);
		pcell->ene[2].setColour(0,1,0,1);
		pcell->ene[3].setColour(0,1,0,1);
		pcell->setjumpable(true);
		pcell->speedup();
	}

}