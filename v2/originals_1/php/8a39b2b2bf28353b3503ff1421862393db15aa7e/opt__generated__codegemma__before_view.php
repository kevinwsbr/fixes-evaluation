```php
<?php
if (!defined('FLUX_ROOT')) exit;
$this->loginRequired(); 
?>
<?php if($ticketlist): ?>
<h2><?php echo Flux::message('SDHeaderID') ?><?php echo htmlspecialchars($trow->ticket_id) ?> - <?php echo htmlspecialchars($trow->subject) ?></h2>
	<table class="vertical-table" width="100%"> 
		<tbody>
		<tr>
			<th>Account</th>
				<td><?php echo $this->linkToAccount($trow->account_id, htmlspecialchars($session->account->userid . ' (' . $session->account->account_id . ')')) ?></td>
			<th>Characters Affected</th>
				<?php if($trow->char_id == '0'):?>
				<td><i>All Characters</i></td>
				<?php elseif($trow->char_id == '-1'):?>
				<td><i>None on account</i></td>
				<?php else:?>
				<td><?php echo $this->linkToCharacter($trow->char_id, htmlspecialchars($char->name)) ?></td>
				<?php endif ?>
		</tr>
		<tr>
			<th>Status</th>
			<td><?php echo htmlspecialchars($trow->status) ?></td>
		</tr>
		<tr>
			<th>Description</th>
			<td><?php echo nl2br(htmlspecialchars($trow->description)) ?></td>
		</tr>
		</tbody>
	</table>
	<br />
	<?php if($trow->status != 'Resolved' || $trow->status != 'Closed'): ?>
	<form action="<?php echo $this->urlWithQs ?>" method="post">
	<table class="vertical-table" width="100%"> 
		<tbody>
		<tr>
			<th width="100">Response</th>
			<td><textarea cols="30" rows="10" name="response" placeholder="Click here to enter a response."></textarea></td>
		</tr>
		<tr>
			<th>Actions</th>
			<td><table class="generic-form-table">
			<?php if($trow->status == "Resolved" || $trow->status == "Closed"): ?>
				<tr><td><?php echo Flux::message('SDRespTable6') ?>:</td><td><input type="radio" name="secact" value="6" checked="checked" /></td></tr>
			<?php else: ?>
			<tr><td><?php echo Flux::message('SDRespTable2') ?>:</td><td><input type="radio" name="secact" value="2" checked="checked" /></td></tr>
			<tr><td><?php echo Flux::message('SDRespTable3') ?>:</td><td><input type="radio" name="secact" value="3" /></td></tr>
			<?php endif ?>
			</table></td>
		</tr>
		<tr>
			<td colspan="2">
			<input type="hidden" name="postreply" value="gogolol" />
			<input type="submit" name="submit" value="Add Reply" /></td>
		</tr>
		</tbody>
	</table>
	</form>
	<?php endif ?>
	
	
<?php else: ?>
	<p>
		<?php echo htmlspecialchars(Flux::message('SDHuh')) ?>
	</p>
<?php endif ?>
