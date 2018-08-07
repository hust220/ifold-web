<script src="style/js/submittask.js" language="javascript" type="text/javascript"></script>
<script src="style/js/ifoldtabs.js" language="javascript" type="text/javascript"></script>

Submit Task:<br/><br/>

{if isset($submitError)}
<div class="errors_box" style="width:90%">
		{$submitError}
</div>
{/if}

{if isset($submitSuccess)}
	Job has been submitted!
{/if}

<h2 class="submitSteps">Step 1: Fill in the General Information</h2>

<!-- Start the Form -->

<form method="post" action="submit.php">
<table id="submitTable" border="0" cellpadding="0" cellspacing="0" class="ifoldTable" style="width:400px">
	<tr>
		<td width="90%">Username:</td>
		<td><input id="username" type="text" disabled="true" value="{$user->get('username')}" /></td>
	</tr>
	<tr>
		<td>Name of Task:</td>
		<td><input type="text" name="name" /></td>
	</tr>
	<tr>
		<td>Description of Task:</td>
		<td><input type="text" name="description" /></td>
	</tr>
</table><br/>
<input id="foldtype" type="hidden" name="foldtype" />
<h2 class="submitSteps">Step 2: Select the Type of Fold and Parameters</h2>
<div id="butUnfolding" onclick="tabOpen('Unfolding')" style="float:left" class="ifoldTabButton">Unfolding</div>
<div id="butThermo" onclick="tabOpen('Thermo')" style="float:left" class="ifoldTabButton">Thermo Scan</div>
<div id="butAnnealing" onclick="tabOpen('Annealing')" style="float:left" class="ifoldTabButton">Annealing</div>
<div id="butCustomFold" onclick="tabOpen('CustomFold')" style="float:left" class="ifoldTabButton">Custom Fold</div>
<div id="butCustomUnfold" onclick="tabOpen('CustomUnfold')" style="float:left" class="ifoldTabButton">Cust. Unfold</div>
<div id="butPfold" onclick="tabOpen('Pfold')" style="float:left" class="ifoldTabButton">pfold Scan</div>
<div id="ifoldTabBody" class="ifoldTabBody">
	
</div>
<input name="action" type="submit" value="Submit Task" />
</form>

<!-- End the Form -->

<div id="tabUnfolding" class="ifoldTabContent">
		<h3>Protein unfolding / Thermal denaturation</h3>
		<div class="tabInfo">
		In unfolding simulations, we start 
with the native structure of the protein, simulated at low temperature and slowly 
raise the temperature of the system until the protein starts to unfold.
		</div>
		<h4>Please Fill in the Required Inputs:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Native Structure of the Protein (PDB Format):</td>
				<td><input type="text" name="pdbFile" /></td>
			</tr>
		</table>
		<h4>Extra Parameters:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Initial Temperature:</td>
				<td><input type="text" name="intialTemp" value="0.4" /></td>
			</tr>
			<tr>
				<td>Final Temperature:</td>
				<td><input type="text" name="finalTemp" value="1.2" /></td>
			</tr>
			<tr>
				<td>Heat Exchange Coefficient:</td>
				<td><input type="text" name="heatC" value="0.0001" /></td>
			</tr>
			<tr>
				<td>Total Simulation Time:</td>
				<td><input type="text" name="maxTime" value="100000" /></td>
			</tr>
		</table>
		<h4>What Kinds of Outputs Would You Like?:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Range of Trajectory Snapshots:</td>
				<td><input type="text" name="trajSnapRange" /></td>
			</tr>
			<tr>
				<td>Graph of Radius of Gyration vs. Simulation Time?</td>
				<td><input type="checkbox" name="gyraVsTime" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Simulation Time?</td>
				<td><input type="checkbox" name="enerVsTime" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Temperature?</td>
				<td><input type="checkbox" name="enerVsTemp" value="1" /></td>
			</tr>
			<tr>
				<td>Mpeg Movie of Simulation?</td>
				<td><input type="checkbox" name="mpegMovie" value="1" /></td>
			</tr>
		</table>
	</div>
	<div id="tabThermo" class="ifoldTabContent">
		<h3>Thermodynamics Scan</h3>
		<div class="tabInfo">
		In this mode we perform constant temperature DMD simulations of the given protein structure 
		over a range of temperatures to get thermodynamic properties of the simulated protein.
		</div>
		<h4>Please Fill in the Required Inputs:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Native Structure of the Protein (PDB Format):</td>
				<td><input type="text" name="pdbFile" /></td>
			</tr>
		</table>
		<h4>Extra Parameters:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Structural Model of the Protein:</td>
				<td><input type="text" name="structModType" value="" /></td>
			</tr>
			<tr>
				<td width="70%">Range of Temperature Scan:</td>
				<td><input type="text" name="tempRangeScan" value="" /></td>
			</tr>
			<tr>
				<td width="70%">Initial Temperature:</td>
				<td><input type="text" name="intialTemp" value="" /></td>
			</tr>
			<tr>
				<td>Final Temperature:</td>
				<td><input type="text" name="finalTemp" value="" /></td>
			</tr>
			<tr>
				<td>Heat Exchange Coefficient:</td>
				<td><input type="text" name="heatC" value="0.1" /></td>
			</tr>
			<tr>
				<td>Total Simulation Time:</td>
				<td><input type="text" name="maxTime" value="100000" /></td>
			</tr>
		</table>
		<h4>What Kinds of Outputs Would You Like?:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td>Graph of Heat Capacity vs. Temperature?</td>
				<td><input type="checkbox" name="heatVsTemp" value="1" /></td>
			</tr>
			<tr>
				<td>Mean Radius of Gyration?</td>
				<td><input type="checkbox" name="gyraRadius" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Temperature?</td>
				<td><input type="checkbox" name="enerVsTemp" value="1" /></td>
			</tr>
			<tr>
				<td>Frequencies of inter-residue contacts made over the given temperature range?</td>
				<td><input type="checkbox" name="frequencies" value="1" /></td>
			</tr>
		</table>
	</div>
	<div id="tabAnnealing" class="ifoldTabContent">
		<h3>Annealing</h3>
		<div class="tabInfo">
		In this mode we start from a high temperature conformation where the protein is unfolded and 
		slowly reduce the temperature to a very low value, whereby the protein folds to a stable 
		conformation. This process is repeated a certain number of times, suddenly raising the 
		temperature from the last stable conformation and allowing the protein to cool at a very 
		slow rate. Multiple runs ensure that the protein reaches the most stable conformation, which 
		is hypothesized to be the native state.
		</div>
		<h4>Please Fill in the Required Inputs:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Native Structure of the Protein (PDB Format):</td>
				<td><input type="text" name="pdbFile" /></td>
			</tr>
		</table>
		<h4>Extra Parameters:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Structural Model of the Protein:</td>
				<td><input type="text" name="structModType" value="" /></td>
			</tr>
			<tr>
				<td width="70%">Number of Runs:</td>
				<td><input type="text" name="numRuns" value="5" /></td>
			</tr>
			<tr>
				<td width="70%">Annealing Step t:</td>
				<td><input type="text" name="annealingT" value="10000" /></td>
			</tr>
			<tr>
				<td>Annealing Step Th:</td>
				<td><input type="text" name="annealingTh" value="2" /></td>
			</tr>
			<tr>
				<td>Annealing Step Tl:</td>
				<td><input type="text" name="annealingTl" value="0.4" /></td>
			</tr>
			<tr>
				<td>Heat Exchange Coefficient:</td>
				<td><input type="text" name="heatC" value="0.0005" /></td>
			</tr>
		</table>
		<h4>What Kinds of Outputs Would You Like?:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td>Final Folded Protein Structure?</td>
				<td><input type="checkbox" name="finalFoldStruct" value="1" /></td>
			</tr>
			<tr>
				<td>Trajectory of All Simulation Runs?</td>
				<td><input type="checkbox" name="trajSnapshots" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Temperature?</td>
				<td><input type="checkbox" name="enerVsTemp" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Number of Runs?</td>
				<td><input type="checkbox" name="enerVsRuns" value="1" /></td>
			</tr>
		</table>
	</div>
	<div id="tabCustomFold" class="ifoldTabContent">
		<h3>Custom Temperature Fold</h3>
		<div class="tabInfo">
		In this mode, folding starts from a linear conformation of the protein at the initial temperature given, 
		and the temperature is reduced at the specified rate until the system reaches the final temperature.
		</div>
		<h4>Please Fill in the Required Inputs:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Native Structure of the Protein (PDB Format):</td>
				<td><input type="text" name="pdbFile" /></td>
			</tr>
			<tr>
				<td width="70%">Initial Temperature:</td>
				<td><input type="text" name="intialTemp" value="" /></td>
			</tr>
			<tr>
				<td>Final Temperature:</td>
				<td><input type="text" name="finalTemp" value="" /></td>
			</tr>
			<tr>
				<td>Rate of Temperature Decrease:</td>
				<td><input type="text" name="alphaRate" value="" /></td>
			</tr>
		</table>
		<h4>What Kinds of Outputs Would You Like?:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Range of Trajectory Snapshots:</td>
				<td><input type="text" name="trajSnapRange" /></td>
			</tr>
			<tr>
				<td>Graph of Mean Radius of Gyration vs. Simulation Time?</td>
				<td><input type="checkbox" name="gyraVsTime" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Simulation Time?</td>
				<td><input type="checkbox" name="enerVsTime" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Temperature?</td>
				<td><input type="checkbox" name="enerVsTemp" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Heat Capacity vs. Temp?</td>
				<td><input type="checkbox" name="heatVsTemp" value="1" /></td>
			</tr>
			<tr>
				<td>RMSD of the Final Conformation with Native Structure?</td>
				<td><input type="checkbox" name="RMSD" value="1" /></td>
			</tr>			
			<tr>
				<td>Mpeg Movie of Simulation?</td>
				<td><input type="checkbox" name="mpegMovie" value="1" /></td>
			</tr>
		</table>
	</div>
	<div id="tabCustomUnfold" class="ifoldTabContent">
		<h3>Custom Temperature Unfold</h3>
		<div class="tabInfo">
		In this mode, folding starts from a linear conformation of the protein at the initial temperature given, 
		and the temperature is increased at the specified rate until the system reaches the final temperature.
		</div>
		<h4>Please Fill in the Required Inputs:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Native Structure of the Protein (PDB Format):</td>
				<td><input type="text" name="pdbFile" /></td>
			</tr>
			<tr>
				<td width="70%">Initial Temperature:</td>
				<td><input type="text" name="intialTemp" value="" /></td>
			</tr>
			<tr>
				<td>Final Temperature:</td>
				<td><input type="text" name="finalTemp" value="" /></td>
			</tr>
			<tr>
				<td>Rate of Temperature Increase:</td>
				<td><input type="text" name="alphaRate" value="" /></td>
			</tr>
		</table>
		<h4>What Kinds of Outputs Would You Like?:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Range of Trajectory Snapshots:</td>
				<td><input type="text" name="trajSnapRange" /></td>
			</tr>
			<tr>
				<td>Graph of Mean Radius of Gyration vs. Simulation Time?</td>
				<td><input type="checkbox" name="gyraVsTime" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Simulation Time?</td>
				<td><input type="checkbox" name="enerVsTime" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Energy vs. Temperature?</td>
				<td><input type="checkbox" name="enerVsTemp" value="1" /></td>
			</tr>
			<tr>
				<td>Graph of Heat Capacity vs. Time?</td>
				<td><input type="checkbox" name="heatVsTime" value="1" /></td>
			</tr>
			<tr>
				<td>Mpeg Movie of Simulation?</td>
				<td><input type="checkbox" name="mpegMovie" value="1" /></td>
			</tr>
		</table>
	</div>
	<div id="tabPfold" class="ifoldTabContent">
		<h3>Pfold</h3>
		<div class="tabInfo">
		Pfold refers to the probability that a given conformation of the protein will fold before unfolding. 
		It is a quantitative measure of progress in protein folding of the given conformation.
		</div>
		<h4>Please Fill in the Required Inputs:</h4>
		<table border="0" cellpadding="0" cellspacing="0" class="ifoldTable submitParamsTable">
			<tr>
				<td width="70%">Native Structure of the Protein (PDB Format):</td>
				<td><input type="text" name="pdbFile" /></td>
			</tr>
			<tr>
				<td width="70%">Structural Model of the Protein:</td>
				<td><input type="text" name="structModType" value="" /></td>
			</tr>
			<tr>
				<td width="70%">Structure of the Decoy:</td>
				<td><input type="text" name="decoyStructure" value="" /></td>
			</tr>						
		</table>
	</div>
	
<script language="javascript" type="text/javascript">
	tabRegister('Unfolding', 'Thermo', 'Annealing', 'CustomFold', 'CustomUnfold', 'Pfold');
</script>